
#ifndef JavaScriptEvaluatorH
#define JavaScriptEvaluatorH

#include <windows.h>
#include <activscp.h>
#include <oleauto.h>
#include <string>

class TScriptSite : public IActiveScriptSite
{
private:
    LONG refCount;

public:

    TScriptSite()
    {
        refCount = 1;
    }

    HRESULT STDMETHODCALLTYPE QueryInterface(
        REFIID riid, void **ppv)
    {
        if (!ppv)
            return E_POINTER;

        *ppv = NULL;

        if (IsEqualIID(riid, IID_IUnknown) ||
            IsEqualIID(riid, IID_IActiveScriptSite))
        {
            *ppv = (IActiveScriptSite*)this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }

    ULONG STDMETHODCALLTYPE AddRef()
    {
        return InterlockedIncrement(&refCount);
    }

    ULONG STDMETHODCALLTYPE Release()
    {
        LONG n = InterlockedDecrement(&refCount);

        if (n == 0)
            delete this;

        return n;
    }

    HRESULT STDMETHODCALLTYPE GetLCID(LCID *lcid)
    {
        if (!lcid)
            return E_POINTER;

        *lcid = LOCALE_USER_DEFAULT;
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE GetItemInfo(
        LPCOLESTR name,
        DWORD mask,
        IUnknown **unknown,
        ITypeInfo **typeInfo)
    {
        if (unknown) *unknown = NULL;
        if (typeInfo) *typeInfo = NULL;

        return TYPE_E_ELEMENTNOTFOUND;
    }

    HRESULT STDMETHODCALLTYPE GetDocVersionString(BSTR *version)
    {
        if (!version)
            return E_POINTER;

        *version = SysAllocString(L"1.0");

        return *version ? S_OK : E_OUTOFMEMORY;
    }

    HRESULT STDMETHODCALLTYPE OnScriptTerminate(
        const VARIANT *result,
        const EXCEPINFO *exceptionInfo)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE OnStateChange(SCRIPTSTATE state)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE OnScriptError(IActiveScriptError *error)
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE OnEnterScript()
    {
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE OnLeaveScript()
    {
        return S_OK;
    }
};


class JavaScriptEvaluator
{
private:

    IActiveScript *engine;
    IActiveScriptParse *parser;
    TScriptSite *site;

    bool initialized;
    bool comInitialized;

    std::wstring result;
    std::wstring error;

    static std::wstring VariantToString(VARIANT *value)
    {
        std::wstring output;

        if (value->vt == VT_EMPTY)
            return L"undefined";

        if (value->vt == VT_NULL)
            return L"null";

        VARIANT converted;
        VariantInit(&converted);

        HRESULT hr = VariantChangeType(
            &converted,
            value,
            0,
            VT_BSTR
        );

        if (SUCCEEDED(hr))
        {
            if (converted.bstrVal)
                output = converted.bstrVal;

            VariantClear(&converted);
        }

        return output;
    }

public:

    JavaScriptEvaluator()
    {
        engine = NULL;
        parser = NULL;
        site = NULL;

        initialized = false;
        comInitialized = false;
    }

    ~JavaScriptEvaluator()
    {
        free();
    }

    bool init()
    {
        if (initialized)
            return true;

        HRESULT hr = CoInitialize(NULL);

        if (FAILED(hr))
            return false;

        comInitialized = true;

        CLSID clsid;

        hr = CLSIDFromProgID(L"JScript", &clsid);

        if (FAILED(hr))
            goto failed;

        hr = CoCreateInstance(
            clsid,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_IActiveScript,
            (void**)&engine
        );

        if (FAILED(hr))
            goto failed;

        site = new TScriptSite();

        hr = engine->SetScriptSite(site);

        if (FAILED(hr))
            goto failed;

        hr = engine->QueryInterface(
            IID_IActiveScriptParse,
            (void**)&parser
        );

        if (FAILED(hr))
            goto failed;

        hr = parser->InitNew();

        if (FAILED(hr))
            goto failed;

        hr = engine->SetScriptState(SCRIPTSTATE_STARTED);

        if (FAILED(hr))
            goto failed;

        initialized = true;

        return true;

    failed:

        free();

        return false;
    }


	bool define(const wchar_t *script)
	{
		return eval(script, false);
	}

	bool eval(const wchar_t *script, bool expression = true)
	{
        if (!initialized || !script)
            return false;

        result.clear();
        error.clear();

        VARIANT value;
        VariantInit(&value);

        EXCEPINFO excep;
        ZeroMemory(&excep, sizeof(excep));

        DWORD flags = expression
            ? SCRIPTTEXT_ISEXPRESSION
            : 0;

        HRESULT hr = parser->ParseScriptText(
            script,
            NULL,
            NULL,
            NULL,
            0,
            0,
            flags,
            &value,
            &excep
        );

        if (FAILED(hr))
        {
            if (excep.bstrDescription)
                error = excep.bstrDescription;

            VariantClear(&value);

            if (excep.bstrSource)
                SysFreeString(excep.bstrSource);

            if (excep.bstrDescription)
                SysFreeString(excep.bstrDescription);

            if (excep.bstrHelpFile)
                SysFreeString(excep.bstrHelpFile);

            return false;
        }

        result = VariantToString(&value);

        VariantClear(&value);

        if (excep.bstrSource)
            SysFreeString(excep.bstrSource);

        if (excep.bstrDescription)
            SysFreeString(excep.bstrDescription);

        if (excep.bstrHelpFile)
            SysFreeString(excep.bstrHelpFile);

        return true;
    }


    const wchar_t *getResult()
    {
        return result.c_str();
    }

    const wchar_t *getError()
    {
        return error.c_str();
    }


    void free()
    {
        initialized = false;

        result.clear();
        error.clear();

        if (parser)
        {
            parser->Release();
            parser = NULL;
        }

        if (engine)
        {
            engine->Close();
            engine->Release();
            engine = NULL;
        }

        if (site)
        {
            site->Release();
            site = NULL;
        }

        if (comInitialized)
        {
            CoUninitialize();
            comInitialized = false;
        }
    }
};

#endif

