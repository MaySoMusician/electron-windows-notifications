// Copyright (c) Microsoft Corporation
// All rights reserved. 
//
// Licensed under the Apache License, Version 2.0 (the ""License""); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 
//
// THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT. 
//
// See the Apache Version 2.0 License for specific language governing permissions and limitations under the License.

// TODO: Verify that this is is still needed..
#define NTDDI_VERSION 0x06010000

#include <v8.h>
#include "nan.h"
#include <string>
#include <ppltasks.h>
#include "CollectionsConverter.h"
#include "CollectionsWrap.h"
#include "node-async.h"
#include "NodeRtUtils.h"
#include "OpaqueWrapper.h"
#include "WrapperBase.h"

#using <Windows.WinMD>

// this undefs fixes the issues of compiling Windows.Data.Json, Windows.Storag.FileProperties, and Windows.Stroage.Search
// Some of the node header files brings windows definitions with the same names as some of the WinRT methods
#undef DocumentProperties
#undef GetObject
#undef CreateEvent
#undef FindText
#undef SendMessage

const char* REGISTRATION_TOKEN_MAP_PROPERTY_NAME = "__registrationTokenMap__";

using v8::Array;
using v8::String;
using v8::Handle;
using v8::Value;
using v8::Boolean;
using v8::Integer;
using v8::FunctionTemplate;
using v8::Object;
using v8::Local;
using v8::Function;
using v8::Date;
using v8::Number;
using v8::PropertyAttribute;
using v8::Primitive;
using Nan::HandleScope;
using Nan::Persistent;
using Nan::Undefined;
using Nan::True;
using Nan::False;
using Nan::Null;
using Nan::MaybeLocal;
using Nan::EscapableHandleScope;
using Nan::HandleScope;
using Nan::TryCatch;
using namespace concurrency;

namespace NodeRT { namespace Windows { namespace ApplicationModel { 

  v8::Local<v8::Value> WrapFullTrustProcessLauncher(::Windows::ApplicationModel::FullTrustProcessLauncher^ wintRtInstance);
  ::Windows::ApplicationModel::FullTrustProcessLauncher^ UnwrapFullTrustProcessLauncher(Local<Value> value);
  
  v8::Local<v8::Value> WrapStartupTask(::Windows::ApplicationModel::StartupTask^ wintRtInstance);
  ::Windows::ApplicationModel::StartupTask^ UnwrapStartupTask(Local<Value> value);
  
  v8::Local<v8::Value> WrapAppDisplayInfo(::Windows::ApplicationModel::AppDisplayInfo^ wintRtInstance);
  ::Windows::ApplicationModel::AppDisplayInfo^ UnwrapAppDisplayInfo(Local<Value> value);
  
  v8::Local<v8::Value> WrapAppInfo(::Windows::ApplicationModel::AppInfo^ wintRtInstance);
  ::Windows::ApplicationModel::AppInfo^ UnwrapAppInfo(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageStatus(::Windows::ApplicationModel::PackageStatus^ wintRtInstance);
  ::Windows::ApplicationModel::PackageStatus^ UnwrapPackageStatus(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageId(::Windows::ApplicationModel::PackageId^ wintRtInstance);
  ::Windows::ApplicationModel::PackageId^ UnwrapPackageId(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackage(::Windows::ApplicationModel::Package^ wintRtInstance);
  ::Windows::ApplicationModel::Package^ UnwrapPackage(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageContentGroup(::Windows::ApplicationModel::PackageContentGroup^ wintRtInstance);
  ::Windows::ApplicationModel::PackageContentGroup^ UnwrapPackageContentGroup(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageStagingEventArgs(::Windows::ApplicationModel::PackageStagingEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::PackageStagingEventArgs^ UnwrapPackageStagingEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageInstallingEventArgs(::Windows::ApplicationModel::PackageInstallingEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::PackageInstallingEventArgs^ UnwrapPackageInstallingEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageUpdatingEventArgs(::Windows::ApplicationModel::PackageUpdatingEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::PackageUpdatingEventArgs^ UnwrapPackageUpdatingEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageUninstallingEventArgs(::Windows::ApplicationModel::PackageUninstallingEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::PackageUninstallingEventArgs^ UnwrapPackageUninstallingEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageStatusChangedEventArgs(::Windows::ApplicationModel::PackageStatusChangedEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::PackageStatusChangedEventArgs^ UnwrapPackageStatusChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageContentGroupStagingEventArgs(::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^ UnwrapPackageContentGroupStagingEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageCatalog(::Windows::ApplicationModel::PackageCatalog^ wintRtInstance);
  ::Windows::ApplicationModel::PackageCatalog^ UnwrapPackageCatalog(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageCatalogAddOptionalPackageResult(::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^ wintRtInstance);
  ::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^ UnwrapPackageCatalogAddOptionalPackageResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageCatalogRemoveOptionalPackagesResult(::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^ wintRtInstance);
  ::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^ UnwrapPackageCatalogRemoveOptionalPackagesResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageCatalogRemoveResourcePackagesResult(::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^ wintRtInstance);
  ::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^ UnwrapPackageCatalogRemoveResourcePackagesResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapPackageCatalogAddResourcePackageResult(::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^ wintRtInstance);
  ::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^ UnwrapPackageCatalogAddResourcePackageResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapDesignMode(::Windows::ApplicationModel::DesignMode^ wintRtInstance);
  ::Windows::ApplicationModel::DesignMode^ UnwrapDesignMode(Local<Value> value);
  
  v8::Local<v8::Value> WrapAppInstance(::Windows::ApplicationModel::AppInstance^ wintRtInstance);
  ::Windows::ApplicationModel::AppInstance^ UnwrapAppInstance(Local<Value> value);
  
  v8::Local<v8::Value> WrapSuspendingEventArgs(::Windows::ApplicationModel::SuspendingEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::SuspendingEventArgs^ UnwrapSuspendingEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapLeavingBackgroundEventArgs(::Windows::ApplicationModel::LeavingBackgroundEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::LeavingBackgroundEventArgs^ UnwrapLeavingBackgroundEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapEnteredBackgroundEventArgs(::Windows::ApplicationModel::EnteredBackgroundEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::EnteredBackgroundEventArgs^ UnwrapEnteredBackgroundEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapISuspendingDeferral(::Windows::ApplicationModel::ISuspendingDeferral^ wintRtInstance);
  ::Windows::ApplicationModel::ISuspendingDeferral^ UnwrapISuspendingDeferral(Local<Value> value);
  
  v8::Local<v8::Value> WrapSuspendingDeferral(::Windows::ApplicationModel::SuspendingDeferral^ wintRtInstance);
  ::Windows::ApplicationModel::SuspendingDeferral^ UnwrapSuspendingDeferral(Local<Value> value);
  
  v8::Local<v8::Value> WrapISuspendingOperation(::Windows::ApplicationModel::ISuspendingOperation^ wintRtInstance);
  ::Windows::ApplicationModel::ISuspendingOperation^ UnwrapISuspendingOperation(Local<Value> value);
  
  v8::Local<v8::Value> WrapSuspendingOperation(::Windows::ApplicationModel::SuspendingOperation^ wintRtInstance);
  ::Windows::ApplicationModel::SuspendingOperation^ UnwrapSuspendingOperation(Local<Value> value);
  
  v8::Local<v8::Value> WrapISuspendingEventArgs(::Windows::ApplicationModel::ISuspendingEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::ISuspendingEventArgs^ UnwrapISuspendingEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapILeavingBackgroundEventArgs(::Windows::ApplicationModel::ILeavingBackgroundEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::ILeavingBackgroundEventArgs^ UnwrapILeavingBackgroundEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapIEnteredBackgroundEventArgs(::Windows::ApplicationModel::IEnteredBackgroundEventArgs^ wintRtInstance);
  ::Windows::ApplicationModel::IEnteredBackgroundEventArgs^ UnwrapIEnteredBackgroundEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapCameraApplicationManager(::Windows::ApplicationModel::CameraApplicationManager^ wintRtInstance);
  ::Windows::ApplicationModel::CameraApplicationManager^ UnwrapCameraApplicationManager(Local<Value> value);
  


  static void InitStartupTaskStateEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("StartupTaskState").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("disabled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::StartupTaskState::Disabled)));
	Nan::Set(enumObject, Nan::New<String>("disabledByUser").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::StartupTaskState::DisabledByUser)));
	Nan::Set(enumObject, Nan::New<String>("enabled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::StartupTaskState::Enabled)));
	Nan::Set(enumObject, Nan::New<String>("disabledByPolicy").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::StartupTaskState::DisabledByPolicy)));
	Nan::Set(enumObject, Nan::New<String>("enabledByPolicy").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::StartupTaskState::EnabledByPolicy)));
  }


  static void InitPackageSignatureKindEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("PackageSignatureKind").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::PackageSignatureKind::None)));
	Nan::Set(enumObject, Nan::New<String>("developer").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::PackageSignatureKind::Developer)));
	Nan::Set(enumObject, Nan::New<String>("enterprise").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::PackageSignatureKind::Enterprise)));
	Nan::Set(enumObject, Nan::New<String>("store").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::PackageSignatureKind::Store)));
	Nan::Set(enumObject, Nan::New<String>("system").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::PackageSignatureKind::System)));
  }


  static void InitAddResourcePackageOptionsEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("AddResourcePackageOptions").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::AddResourcePackageOptions::None)));
	Nan::Set(enumObject, Nan::New<String>("forceTargetAppShutdown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::AddResourcePackageOptions::ForceTargetAppShutdown)));
	Nan::Set(enumObject, Nan::New<String>("applyUpdateIfAvailable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::AddResourcePackageOptions::ApplyUpdateIfAvailable)));
  }


  static void InitPackageContentGroupStateEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("PackageContentGroupState").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("notStaged").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::PackageContentGroupState::NotStaged)));
	Nan::Set(enumObject, Nan::New<String>("queued").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::PackageContentGroupState::Queued)));
	Nan::Set(enumObject, Nan::New<String>("staging").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::PackageContentGroupState::Staging)));
	Nan::Set(enumObject, Nan::New<String>("staged").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::ApplicationModel::PackageContentGroupState::Staged)));
  }



  
  static bool IsFullTrustAppContractJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::ApplicationModel::FullTrustAppContract FullTrustAppContractFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::ApplicationModel::FullTrustAppContract returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> FullTrustAppContractToJsObject(::Windows::ApplicationModel::FullTrustAppContract value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    
    return scope.Escape(obj);
  }

  
  static bool IsStartupTaskContractJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::ApplicationModel::StartupTaskContract StartupTaskContractFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::ApplicationModel::StartupTaskContract returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> StartupTaskContractToJsObject(::Windows::ApplicationModel::StartupTaskContract value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    
    return scope.Escape(obj);
  }

  
  static bool IsPackageVersionJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("major").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsInt32())
      {
          return false;
      }
    }
    
    symbol = Nan::New<String>("minor").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsInt32())
      {
          return false;
      }
    }
    
    symbol = Nan::New<String>("build").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsInt32())
      {
          return false;
      }
    }
    
    symbol = Nan::New<String>("revision").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsInt32())
      {
          return false;
      }
    }
    
    return true;
  }

  ::Windows::ApplicationModel::PackageVersion PackageVersionFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::ApplicationModel::PackageVersion returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("major").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      returnValue.Major = static_cast<unsigned short>(Nan::To<int32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("minor").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      returnValue.Minor = static_cast<unsigned short>(Nan::To<int32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("build").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      returnValue.Build = static_cast<unsigned short>(Nan::To<int32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("revision").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      returnValue.Revision = static_cast<unsigned short>(Nan::To<int32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    return returnValue;
  }

  Local<Value> PackageVersionToJsObject(::Windows::ApplicationModel::PackageVersion value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("major").ToLocalChecked(), Nan::New<Integer>(value.Major));
    Nan::Set(obj, Nan::New<String>("minor").ToLocalChecked(), Nan::New<Integer>(value.Minor));
    Nan::Set(obj, Nan::New<String>("build").ToLocalChecked(), Nan::New<Integer>(value.Build));
    Nan::Set(obj, Nan::New<String>("revision").ToLocalChecked(), Nan::New<Integer>(value.Revision));
    
    return scope.Escape(obj);
  }

  
  static bool IsPackageInstallProgressJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("percentComplete").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsUint32())
      {
          return false;
      }
    }
    
    return true;
  }

  ::Windows::ApplicationModel::PackageInstallProgress PackageInstallProgressFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::ApplicationModel::PackageInstallProgress returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("percentComplete").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false))
    {
      returnValue.PercentComplete = static_cast<unsigned int>(Nan::To<uint32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    return returnValue;
  }

  Local<Value> PackageInstallProgressToJsObject(::Windows::ApplicationModel::PackageInstallProgress value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("percentComplete").ToLocalChecked(), Nan::New<Integer>(value.PercentComplete));
    
    return scope.Escape(obj);
  }

  
  static bool IsSizeJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Foundation::Size SizeFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::Foundation::Size returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> SizeToJsObject(::Windows::Foundation::Size value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    
    return scope.Escape(obj);
  }

  
  class FullTrustProcessLauncher : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("FullTrustProcessLauncher").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      func = Nan::GetFunction(Nan::New<FunctionTemplate>(LaunchFullTrustProcessForCurrentAppAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("launchFullTrustProcessForCurrentAppAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(LaunchFullTrustProcessForAppAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("launchFullTrustProcessForAppAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("FullTrustProcessLauncher").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    FullTrustProcessLauncher(::Windows::ApplicationModel::FullTrustProcessLauncher^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::FullTrustProcessLauncher^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::FullTrustProcessLauncher^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::FullTrustProcessLauncher^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      FullTrustProcessLauncher *wrapperInstance = new FullTrustProcessLauncher(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::FullTrustProcessLauncher^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::FullTrustProcessLauncher^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::FullTrustProcessLauncher^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapFullTrustProcessLauncher(winRtInstance));
    }


  

    static void LaunchFullTrustProcessForCurrentAppAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncAction^ op;
      

      if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::ApplicationModel::FullTrustProcessLauncher::LaunchFullTrustProcessForCurrentAppAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = ::Windows::ApplicationModel::FullTrustProcessLauncher::LaunchFullTrustProcessForCurrentAppAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) 
      {	
        try
        {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
          
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void LaunchFullTrustProcessForAppAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncAction^ op;
      

      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = ::Windows::ApplicationModel::FullTrustProcessLauncher::LaunchFullTrustProcessForAppAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          
          op = ::Windows::ApplicationModel::FullTrustProcessLauncher::LaunchFullTrustProcessForAppAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) 
      {	
        try
        {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
          
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }




  private:
    ::Windows::ApplicationModel::FullTrustProcessLauncher^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapFullTrustProcessLauncher(::Windows::ApplicationModel::FullTrustProcessLauncher^ wintRtInstance);
    friend ::Windows::ApplicationModel::FullTrustProcessLauncher^ UnwrapFullTrustProcessLauncher(Local<Value> value);
  };
  Persistent<FunctionTemplate> FullTrustProcessLauncher::s_constructorTemplate;

  v8::Local<v8::Value> WrapFullTrustProcessLauncher(::Windows::ApplicationModel::FullTrustProcessLauncher^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(FullTrustProcessLauncher::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::FullTrustProcessLauncher^ UnwrapFullTrustProcessLauncher(Local<Value> value)
  {
     return FullTrustProcessLauncher::Unwrap<FullTrustProcessLauncher>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitFullTrustProcessLauncher(Local<Object> exports)
  {
    FullTrustProcessLauncher::Init(exports);
  }

  class StartupTask : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("StartupTask").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "disable", Disable);
      
            
      Nan::SetPrototypeMethod(localRef, "requestEnableAsync", RequestEnableAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("state").ToLocalChecked(), StateGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("taskId").ToLocalChecked(), TaskIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetForCurrentPackageAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("getForCurrentPackageAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("getAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("StartupTask").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    StartupTask(::Windows::ApplicationModel::StartupTask^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::StartupTask^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::StartupTask^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::StartupTask^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StartupTask *wrapperInstance = new StartupTask(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::StartupTask^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::StartupTask^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::StartupTask^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapStartupTask(winRtInstance));
    }


    static void RequestEnableAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::StartupTask^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      StartupTask *wrapper = StartupTask::Unwrap<StartupTask>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::ApplicationModel::StartupTaskState>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->RequestEnableAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::ApplicationModel::StartupTaskState> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(static_cast<int>(result));
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void Disable(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::StartupTask^>(info.This()))
      {
        return;
      }

      StartupTask *wrapper = StartupTask::Unwrap<StartupTask>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Disable();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void GetForCurrentPackageAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::ApplicationModel::StartupTask^>^>^ op;
      

      if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::ApplicationModel::StartupTask::GetForCurrentPackageAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::ApplicationModel::StartupTask^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::ApplicationModel::StartupTask^>::CreateVectorViewWrapper(result, 
            [](::Windows::ApplicationModel::StartupTask^ val) -> Local<Value> {
              return WrapStartupTask(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::StartupTask^>(value);
            },
            [](Local<Value> value) -> ::Windows::ApplicationModel::StartupTask^ {
              return UnwrapStartupTask(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
          
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void GetAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::ApplicationModel::StartupTask^>^ op;
      

      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = ::Windows::ApplicationModel::StartupTask::GetAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::ApplicationModel::StartupTask^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStartupTask(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
          
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }


    static void StateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::StartupTask^>(info.This()))
      {
        return;
      }

      StartupTask *wrapper = StartupTask::Unwrap<StartupTask>(info.This());

      try 
      {
        ::Windows::ApplicationModel::StartupTaskState result = wrapper->_instance->State;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TaskIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::StartupTask^>(info.This()))
      {
        return;
      }

      StartupTask *wrapper = StartupTask::Unwrap<StartupTask>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->TaskId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::StartupTask^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapStartupTask(::Windows::ApplicationModel::StartupTask^ wintRtInstance);
    friend ::Windows::ApplicationModel::StartupTask^ UnwrapStartupTask(Local<Value> value);
  };
  Persistent<FunctionTemplate> StartupTask::s_constructorTemplate;

  v8::Local<v8::Value> WrapStartupTask(::Windows::ApplicationModel::StartupTask^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StartupTask::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::StartupTask^ UnwrapStartupTask(Local<Value> value)
  {
     return StartupTask::Unwrap<StartupTask>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStartupTask(Local<Object> exports)
  {
    StartupTask::Init(exports);
  }

  class AppDisplayInfo : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("AppDisplayInfo").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getLogo", GetLogo);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("description").ToLocalChecked(), DescriptionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayName").ToLocalChecked(), DisplayNameGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("AppDisplayInfo").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    AppDisplayInfo(::Windows::ApplicationModel::AppDisplayInfo^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::AppDisplayInfo^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppDisplayInfo^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::AppDisplayInfo^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      AppDisplayInfo *wrapperInstance = new AppDisplayInfo(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppDisplayInfo^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::AppDisplayInfo^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::AppDisplayInfo^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapAppDisplayInfo(winRtInstance));
    }


  
    static void GetLogo(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppDisplayInfo^>(info.This()))
      {
        return;
      }

      AppDisplayInfo *wrapper = AppDisplayInfo::Unwrap<AppDisplayInfo>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsSize(info[0]))
      {
        try
        {
          ::Windows::Foundation::Size arg0 = NodeRT::Utils::SizeFromJs(info[0]);
          
          ::Windows::Storage::Streams::RandomAccessStreamReference^ result;
          result = wrapper->_instance->GetLogo(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "RandomAccessStreamReference", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void DescriptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppDisplayInfo^>(info.This()))
      {
        return;
      }

      AppDisplayInfo *wrapper = AppDisplayInfo::Unwrap<AppDisplayInfo>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Description;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppDisplayInfo^>(info.This()))
      {
        return;
      }

      AppDisplayInfo *wrapper = AppDisplayInfo::Unwrap<AppDisplayInfo>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->DisplayName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::AppDisplayInfo^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapAppDisplayInfo(::Windows::ApplicationModel::AppDisplayInfo^ wintRtInstance);
    friend ::Windows::ApplicationModel::AppDisplayInfo^ UnwrapAppDisplayInfo(Local<Value> value);
  };
  Persistent<FunctionTemplate> AppDisplayInfo::s_constructorTemplate;

  v8::Local<v8::Value> WrapAppDisplayInfo(::Windows::ApplicationModel::AppDisplayInfo^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(AppDisplayInfo::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::AppDisplayInfo^ UnwrapAppDisplayInfo(Local<Value> value)
  {
     return AppDisplayInfo::Unwrap<AppDisplayInfo>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitAppDisplayInfo(Local<Object> exports)
  {
    AppDisplayInfo::Init(exports);
  }

  class AppInfo : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("AppInfo").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("appUserModelId").ToLocalChecked(), AppUserModelIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayInfo").ToLocalChecked(), DisplayInfoGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("packageFamilyName").ToLocalChecked(), PackageFamilyNameGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("AppInfo").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    AppInfo(::Windows::ApplicationModel::AppInfo^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::AppInfo^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInfo^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::AppInfo^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      AppInfo *wrapperInstance = new AppInfo(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInfo^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::AppInfo^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::AppInfo^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapAppInfo(winRtInstance));
    }


  



    static void AppUserModelIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInfo^>(info.This()))
      {
        return;
      }

      AppInfo *wrapper = AppInfo::Unwrap<AppInfo>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->AppUserModelId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DisplayInfoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInfo^>(info.This()))
      {
        return;
      }

      AppInfo *wrapper = AppInfo::Unwrap<AppInfo>(info.This());

      try 
      {
        ::Windows::ApplicationModel::AppDisplayInfo^ result = wrapper->_instance->DisplayInfo;
        info.GetReturnValue().Set(WrapAppDisplayInfo(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInfo^>(info.This()))
      {
        return;
      }

      AppInfo *wrapper = AppInfo::Unwrap<AppInfo>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Id;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PackageFamilyNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInfo^>(info.This()))
      {
        return;
      }

      AppInfo *wrapper = AppInfo::Unwrap<AppInfo>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->PackageFamilyName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::AppInfo^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapAppInfo(::Windows::ApplicationModel::AppInfo^ wintRtInstance);
    friend ::Windows::ApplicationModel::AppInfo^ UnwrapAppInfo(Local<Value> value);
  };
  Persistent<FunctionTemplate> AppInfo::s_constructorTemplate;

  v8::Local<v8::Value> WrapAppInfo(::Windows::ApplicationModel::AppInfo^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(AppInfo::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::AppInfo^ UnwrapAppInfo(Local<Value> value)
  {
     return AppInfo::Unwrap<AppInfo>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitAppInfo(Local<Object> exports)
  {
    AppInfo::Init(exports);
  }

  class PackageStatus : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageStatus").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "verifyIsOK", VerifyIsOK);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dataOffline").ToLocalChecked(), DataOfflineGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dependencyIssue").ToLocalChecked(), DependencyIssueGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deploymentInProgress").ToLocalChecked(), DeploymentInProgressGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("disabled").ToLocalChecked(), DisabledGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("licenseIssue").ToLocalChecked(), LicenseIssueGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("modified").ToLocalChecked(), ModifiedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("needsRemediation").ToLocalChecked(), NeedsRemediationGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("notAvailable").ToLocalChecked(), NotAvailableGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("packageOffline").ToLocalChecked(), PackageOfflineGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("servicing").ToLocalChecked(), ServicingGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("tampered").ToLocalChecked(), TamperedGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isPartiallyStaged").ToLocalChecked(), IsPartiallyStagedGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageStatus").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageStatus(::Windows::ApplicationModel::PackageStatus^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageStatus^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageStatus^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageStatus *wrapperInstance = new PackageStatus(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageStatus^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageStatus^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageStatus(winRtInstance));
    }


  
    static void VerifyIsOK(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = wrapper->_instance->VerifyIsOK();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void DataOfflineGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->DataOffline;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DependencyIssueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->DependencyIssue;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DeploymentInProgressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->DeploymentInProgress;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DisabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->Disabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LicenseIssueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->LicenseIssue;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ModifiedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->Modified;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NeedsRemediationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->NeedsRemediation;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NotAvailableGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->NotAvailable;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PackageOfflineGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->PackageOffline;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ServicingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->Servicing;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TamperedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->Tampered;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsPartiallyStagedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatus^>(info.This()))
      {
        return;
      }

      PackageStatus *wrapper = PackageStatus::Unwrap<PackageStatus>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsPartiallyStaged;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageStatus^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageStatus(::Windows::ApplicationModel::PackageStatus^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageStatus^ UnwrapPackageStatus(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageStatus::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageStatus(::Windows::ApplicationModel::PackageStatus^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageStatus::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageStatus^ UnwrapPackageStatus(Local<Value> value)
  {
     return PackageStatus::Unwrap<PackageStatus>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageStatus(Local<Object> exports)
  {
    PackageStatus::Init(exports);
  }

  class PackageId : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageId").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("architecture").ToLocalChecked(), ArchitectureGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("familyName").ToLocalChecked(), FamilyNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("fullName").ToLocalChecked(), FullNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publisher").ToLocalChecked(), PublisherGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publisherId").ToLocalChecked(), PublisherIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("resourceId").ToLocalChecked(), ResourceIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("version").ToLocalChecked(), VersionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("author").ToLocalChecked(), AuthorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("productId").ToLocalChecked(), ProductIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageId").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageId(::Windows::ApplicationModel::PackageId^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageId^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageId^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageId *wrapperInstance = new PackageId(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageId^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageId^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageId(winRtInstance));
    }


  



    static void ArchitectureGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info.This()))
      {
        return;
      }

      PackageId *wrapper = PackageId::Unwrap<PackageId>(info.This());

      try 
      {
        ::Windows::System::ProcessorArchitecture result = wrapper->_instance->Architecture;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void FamilyNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info.This()))
      {
        return;
      }

      PackageId *wrapper = PackageId::Unwrap<PackageId>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->FamilyName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void FullNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info.This()))
      {
        return;
      }

      PackageId *wrapper = PackageId::Unwrap<PackageId>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->FullName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info.This()))
      {
        return;
      }

      PackageId *wrapper = PackageId::Unwrap<PackageId>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Name;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PublisherGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info.This()))
      {
        return;
      }

      PackageId *wrapper = PackageId::Unwrap<PackageId>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Publisher;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PublisherIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info.This()))
      {
        return;
      }

      PackageId *wrapper = PackageId::Unwrap<PackageId>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->PublisherId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ResourceIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info.This()))
      {
        return;
      }

      PackageId *wrapper = PackageId::Unwrap<PackageId>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->ResourceId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void VersionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info.This()))
      {
        return;
      }

      PackageId *wrapper = PackageId::Unwrap<PackageId>(info.This());

      try 
      {
        ::Windows::ApplicationModel::PackageVersion result = wrapper->_instance->Version;
        info.GetReturnValue().Set(PackageVersionToJsObject(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void AuthorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info.This()))
      {
        return;
      }

      PackageId *wrapper = PackageId::Unwrap<PackageId>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Author;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProductIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageId^>(info.This()))
      {
        return;
      }

      PackageId *wrapper = PackageId::Unwrap<PackageId>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->ProductId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageId^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageId(::Windows::ApplicationModel::PackageId^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageId^ UnwrapPackageId(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageId::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageId(::Windows::ApplicationModel::PackageId^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageId::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageId^ UnwrapPackageId(Local<Value> value)
  {
     return PackageId::Unwrap<PackageId>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageId(Local<Object> exports)
  {
    PackageId::Init(exports);
  }

  class Package : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("Package").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
            
      Nan::SetPrototypeMethod(localRef, "getThumbnailToken", GetThumbnailToken);
      Nan::SetPrototypeMethod(localRef, "launch", Launch);
      
            
      Nan::SetPrototypeMethod(localRef, "getAppListEntriesAsync", GetAppListEntriesAsync);
      Nan::SetPrototypeMethod(localRef, "verifyContentIntegrityAsync", VerifyContentIntegrityAsync);
      Nan::SetPrototypeMethod(localRef, "getContentGroupsAsync", GetContentGroupsAsync);
      Nan::SetPrototypeMethod(localRef, "getContentGroupAsync", GetContentGroupAsync);
      Nan::SetPrototypeMethod(localRef, "stageContentGroupsAsync", StageContentGroupsAsync);
      Nan::SetPrototypeMethod(localRef, "setInUseAsync", SetInUseAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dependencies").ToLocalChecked(), DependenciesGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("installedLocation").ToLocalChecked(), InstalledLocationGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isFramework").ToLocalChecked(), IsFrameworkGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("description").ToLocalChecked(), DescriptionGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayName").ToLocalChecked(), DisplayNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isBundle").ToLocalChecked(), IsBundleGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isDevelopmentMode").ToLocalChecked(), IsDevelopmentModeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isResourcePackage").ToLocalChecked(), IsResourcePackageGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("logo").ToLocalChecked(), LogoGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publisherDisplayName").ToLocalChecked(), PublisherDisplayNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("installedDate").ToLocalChecked(), InstalledDateGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("status").ToLocalChecked(), StatusGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isOptional").ToLocalChecked(), IsOptionalGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("signatureKind").ToLocalChecked(), SignatureKindGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("installDate").ToLocalChecked(), InstallDateGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetAccessor(constructor, Nan::New<String>("current").ToLocalChecked(), CurrentGetter);

      Nan::Set(exports, Nan::New<String>("Package").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    Package(::Windows::ApplicationModel::Package^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::Package^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::Package^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      Package *wrapperInstance = new Package(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::Package^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::Package^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackage(winRtInstance));
    }


    static void GetAppListEntriesAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::ApplicationModel::Core::AppListEntry^>^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetAppListEntriesAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::ApplicationModel::Core::AppListEntry^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::ApplicationModel::Core::AppListEntry^>::CreateVectorViewWrapper(result, 
            [](::Windows::ApplicationModel::Core::AppListEntry^ val) -> Local<Value> {
              return NodeRT::Utils::CreateExternalWinRTObject("Windows.ApplicationModel.Core", "AppListEntry", val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Core::AppListEntry^>(value);
            },
            [](Local<Value> value) -> ::Windows::ApplicationModel::Core::AppListEntry^ {
              return dynamic_cast<::Windows::ApplicationModel::Core::AppListEntry^>(NodeRT::Utils::GetObjectInstance(value));
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void VerifyContentIntegrityAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->VerifyContentIntegrityAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void GetContentGroupsAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVector<::Windows::ApplicationModel::PackageContentGroup^>^>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetContentGroupsAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVector<::Windows::ApplicationModel::PackageContentGroup^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorWrapper<::Windows::ApplicationModel::PackageContentGroup^>::CreateVectorWrapper(result, 
            [](::Windows::ApplicationModel::PackageContentGroup^ val) -> Local<Value> {
              return WrapPackageContentGroup(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroup^>(value);
            },
            [](Local<Value> value) -> ::Windows::ApplicationModel::PackageContentGroup^ {
              return UnwrapPackageContentGroup(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void GetContentGroupAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::ApplicationModel::PackageContentGroup^>^ op;
    

      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = wrapper->_instance->GetContentGroupAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::ApplicationModel::PackageContentGroup^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapPackageContentGroup(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void StageContentGroupsAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVector<::Windows::ApplicationModel::PackageContentGroup^>^>^ op;
    

      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->StageContentGroupsAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsBoolean())
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          bool arg1 = Nan::To<bool>(info[1]).FromMaybe(false);
          
          op = wrapper->_instance->StageContentGroupsAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVector<::Windows::ApplicationModel::PackageContentGroup^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorWrapper<::Windows::ApplicationModel::PackageContentGroup^>::CreateVectorWrapper(result, 
            [](::Windows::ApplicationModel::PackageContentGroup^ val) -> Local<Value> {
              return WrapPackageContentGroup(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroup^>(value);
            },
            [](Local<Value> value) -> ::Windows::ApplicationModel::PackageContentGroup^ {
              return UnwrapPackageContentGroup(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void SetInUseAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 2
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          op = wrapper->_instance->SetInUseAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  
    static void GetThumbnailToken(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetThumbnailToken();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Launch(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          wrapper->_instance->Launch(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void DependenciesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::ApplicationModel::Package^>^ result = wrapper->_instance->Dependencies;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::ApplicationModel::Package^>::CreateVectorViewWrapper(result, 
            [](::Windows::ApplicationModel::Package^ val) -> Local<Value> {
              return WrapPackage(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(value);
            },
            [](Local<Value> value) -> ::Windows::ApplicationModel::Package^ {
              return UnwrapPackage(value);
            }
          ));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        ::Windows::ApplicationModel::PackageId^ result = wrapper->_instance->Id;
        info.GetReturnValue().Set(WrapPackageId(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InstalledLocationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        ::Windows::Storage::StorageFolder^ result = wrapper->_instance->InstalledLocation;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage", "StorageFolder", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsFrameworkGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsFramework;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DescriptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Description;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->DisplayName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsBundleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsBundle;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsDevelopmentModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsDevelopmentMode;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsResourcePackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsResourcePackage;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->Logo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PublisherDisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->PublisherDisplayName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InstalledDateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->InstalledDate;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StatusGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        ::Windows::ApplicationModel::PackageStatus^ result = wrapper->_instance->Status;
        info.GetReturnValue().Set(WrapPackageStatus(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsOptionalGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsOptional;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SignatureKindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        ::Windows::ApplicationModel::PackageSignatureKind result = wrapper->_instance->SignatureKind;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void InstallDateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(info.This()))
      {
        return;
      }

      Package *wrapper = Package::Unwrap<Package>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->InstallDate;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

    static void CurrentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Windows::ApplicationModel::Package^ result = ::Windows::ApplicationModel::Package::Current;
        info.GetReturnValue().Set(WrapPackage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

  private:
    ::Windows::ApplicationModel::Package^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackage(::Windows::ApplicationModel::Package^ wintRtInstance);
    friend ::Windows::ApplicationModel::Package^ UnwrapPackage(Local<Value> value);
  };
  Persistent<FunctionTemplate> Package::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackage(::Windows::ApplicationModel::Package^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Package::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::Package^ UnwrapPackage(Local<Value> value)
  {
     return Package::Unwrap<Package>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackage(Local<Object> exports)
  {
    Package::Init(exports);
  }

  class PackageContentGroup : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageContentGroup").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isRequired").ToLocalChecked(), IsRequiredGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("package").ToLocalChecked(), PackageGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("state").ToLocalChecked(), StateGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetAccessor(constructor, Nan::New<String>("requiredGroupName").ToLocalChecked(), RequiredGroupNameGetter);

      Nan::Set(exports, Nan::New<String>("PackageContentGroup").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageContentGroup(::Windows::ApplicationModel::PackageContentGroup^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageContentGroup^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroup^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageContentGroup^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageContentGroup *wrapperInstance = new PackageContentGroup(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroup^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageContentGroup^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageContentGroup^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageContentGroup(winRtInstance));
    }


  



    static void IsRequiredGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroup^>(info.This()))
      {
        return;
      }

      PackageContentGroup *wrapper = PackageContentGroup::Unwrap<PackageContentGroup>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsRequired;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroup^>(info.This()))
      {
        return;
      }

      PackageContentGroup *wrapper = PackageContentGroup::Unwrap<PackageContentGroup>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Name;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroup^>(info.This()))
      {
        return;
      }

      PackageContentGroup *wrapper = PackageContentGroup::Unwrap<PackageContentGroup>(info.This());

      try 
      {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->Package;
        info.GetReturnValue().Set(WrapPackage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroup^>(info.This()))
      {
        return;
      }

      PackageContentGroup *wrapper = PackageContentGroup::Unwrap<PackageContentGroup>(info.This());

      try 
      {
        ::Windows::ApplicationModel::PackageContentGroupState result = wrapper->_instance->State;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

    static void RequiredGroupNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::ApplicationModel::PackageContentGroup::RequiredGroupName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

  private:
    ::Windows::ApplicationModel::PackageContentGroup^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageContentGroup(::Windows::ApplicationModel::PackageContentGroup^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageContentGroup^ UnwrapPackageContentGroup(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageContentGroup::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageContentGroup(::Windows::ApplicationModel::PackageContentGroup^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageContentGroup::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageContentGroup^ UnwrapPackageContentGroup(Local<Value> value)
  {
     return PackageContentGroup::Unwrap<PackageContentGroup>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageContentGroup(Local<Object> exports)
  {
    PackageContentGroup::Init(exports);
  }

  class PackageStagingEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageStagingEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("activityId").ToLocalChecked(), ActivityIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("errorCode").ToLocalChecked(), ErrorCodeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isComplete").ToLocalChecked(), IsCompleteGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("package").ToLocalChecked(), PackageGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("progress").ToLocalChecked(), ProgressGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageStagingEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageStagingEventArgs(::Windows::ApplicationModel::PackageStagingEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageStagingEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStagingEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageStagingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageStagingEventArgs *wrapperInstance = new PackageStagingEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStagingEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageStagingEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageStagingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageStagingEventArgs(winRtInstance));
    }


  



    static void ActivityIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageStagingEventArgs *wrapper = PackageStagingEventArgs::Unwrap<PackageStagingEventArgs>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->ActivityId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ErrorCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageStagingEventArgs *wrapper = PackageStagingEventArgs::Unwrap<PackageStagingEventArgs>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ErrorCode;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsCompleteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageStagingEventArgs *wrapper = PackageStagingEventArgs::Unwrap<PackageStagingEventArgs>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsComplete;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageStagingEventArgs *wrapper = PackageStagingEventArgs::Unwrap<PackageStagingEventArgs>(info.This());

      try 
      {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->Package;
        info.GetReturnValue().Set(WrapPackage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProgressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageStagingEventArgs *wrapper = PackageStagingEventArgs::Unwrap<PackageStagingEventArgs>(info.This());

      try 
      {
        double result = wrapper->_instance->Progress;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageStagingEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageStagingEventArgs(::Windows::ApplicationModel::PackageStagingEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageStagingEventArgs^ UnwrapPackageStagingEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageStagingEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageStagingEventArgs(::Windows::ApplicationModel::PackageStagingEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageStagingEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageStagingEventArgs^ UnwrapPackageStagingEventArgs(Local<Value> value)
  {
     return PackageStagingEventArgs::Unwrap<PackageStagingEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageStagingEventArgs(Local<Object> exports)
  {
    PackageStagingEventArgs::Init(exports);
  }

  class PackageInstallingEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageInstallingEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("activityId").ToLocalChecked(), ActivityIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("errorCode").ToLocalChecked(), ErrorCodeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isComplete").ToLocalChecked(), IsCompleteGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("package").ToLocalChecked(), PackageGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("progress").ToLocalChecked(), ProgressGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageInstallingEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageInstallingEventArgs(::Windows::ApplicationModel::PackageInstallingEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageInstallingEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageInstallingEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageInstallingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageInstallingEventArgs *wrapperInstance = new PackageInstallingEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageInstallingEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageInstallingEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageInstallingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageInstallingEventArgs(winRtInstance));
    }


  



    static void ActivityIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageInstallingEventArgs^>(info.This()))
      {
        return;
      }

      PackageInstallingEventArgs *wrapper = PackageInstallingEventArgs::Unwrap<PackageInstallingEventArgs>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->ActivityId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ErrorCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageInstallingEventArgs^>(info.This()))
      {
        return;
      }

      PackageInstallingEventArgs *wrapper = PackageInstallingEventArgs::Unwrap<PackageInstallingEventArgs>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ErrorCode;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsCompleteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageInstallingEventArgs^>(info.This()))
      {
        return;
      }

      PackageInstallingEventArgs *wrapper = PackageInstallingEventArgs::Unwrap<PackageInstallingEventArgs>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsComplete;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageInstallingEventArgs^>(info.This()))
      {
        return;
      }

      PackageInstallingEventArgs *wrapper = PackageInstallingEventArgs::Unwrap<PackageInstallingEventArgs>(info.This());

      try 
      {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->Package;
        info.GetReturnValue().Set(WrapPackage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProgressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageInstallingEventArgs^>(info.This()))
      {
        return;
      }

      PackageInstallingEventArgs *wrapper = PackageInstallingEventArgs::Unwrap<PackageInstallingEventArgs>(info.This());

      try 
      {
        double result = wrapper->_instance->Progress;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageInstallingEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageInstallingEventArgs(::Windows::ApplicationModel::PackageInstallingEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageInstallingEventArgs^ UnwrapPackageInstallingEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageInstallingEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageInstallingEventArgs(::Windows::ApplicationModel::PackageInstallingEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageInstallingEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageInstallingEventArgs^ UnwrapPackageInstallingEventArgs(Local<Value> value)
  {
     return PackageInstallingEventArgs::Unwrap<PackageInstallingEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageInstallingEventArgs(Local<Object> exports)
  {
    PackageInstallingEventArgs::Init(exports);
  }

  class PackageUpdatingEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageUpdatingEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("activityId").ToLocalChecked(), ActivityIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("errorCode").ToLocalChecked(), ErrorCodeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isComplete").ToLocalChecked(), IsCompleteGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("progress").ToLocalChecked(), ProgressGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("sourcePackage").ToLocalChecked(), SourcePackageGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("targetPackage").ToLocalChecked(), TargetPackageGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageUpdatingEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageUpdatingEventArgs(::Windows::ApplicationModel::PackageUpdatingEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageUpdatingEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUpdatingEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageUpdatingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageUpdatingEventArgs *wrapperInstance = new PackageUpdatingEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUpdatingEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageUpdatingEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageUpdatingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageUpdatingEventArgs(winRtInstance));
    }


  



    static void ActivityIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUpdatingEventArgs^>(info.This()))
      {
        return;
      }

      PackageUpdatingEventArgs *wrapper = PackageUpdatingEventArgs::Unwrap<PackageUpdatingEventArgs>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->ActivityId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ErrorCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUpdatingEventArgs^>(info.This()))
      {
        return;
      }

      PackageUpdatingEventArgs *wrapper = PackageUpdatingEventArgs::Unwrap<PackageUpdatingEventArgs>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ErrorCode;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsCompleteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUpdatingEventArgs^>(info.This()))
      {
        return;
      }

      PackageUpdatingEventArgs *wrapper = PackageUpdatingEventArgs::Unwrap<PackageUpdatingEventArgs>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsComplete;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProgressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUpdatingEventArgs^>(info.This()))
      {
        return;
      }

      PackageUpdatingEventArgs *wrapper = PackageUpdatingEventArgs::Unwrap<PackageUpdatingEventArgs>(info.This());

      try 
      {
        double result = wrapper->_instance->Progress;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SourcePackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUpdatingEventArgs^>(info.This()))
      {
        return;
      }

      PackageUpdatingEventArgs *wrapper = PackageUpdatingEventArgs::Unwrap<PackageUpdatingEventArgs>(info.This());

      try 
      {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->SourcePackage;
        info.GetReturnValue().Set(WrapPackage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TargetPackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUpdatingEventArgs^>(info.This()))
      {
        return;
      }

      PackageUpdatingEventArgs *wrapper = PackageUpdatingEventArgs::Unwrap<PackageUpdatingEventArgs>(info.This());

      try 
      {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->TargetPackage;
        info.GetReturnValue().Set(WrapPackage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageUpdatingEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageUpdatingEventArgs(::Windows::ApplicationModel::PackageUpdatingEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageUpdatingEventArgs^ UnwrapPackageUpdatingEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageUpdatingEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageUpdatingEventArgs(::Windows::ApplicationModel::PackageUpdatingEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageUpdatingEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageUpdatingEventArgs^ UnwrapPackageUpdatingEventArgs(Local<Value> value)
  {
     return PackageUpdatingEventArgs::Unwrap<PackageUpdatingEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageUpdatingEventArgs(Local<Object> exports)
  {
    PackageUpdatingEventArgs::Init(exports);
  }

  class PackageUninstallingEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageUninstallingEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("activityId").ToLocalChecked(), ActivityIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("errorCode").ToLocalChecked(), ErrorCodeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isComplete").ToLocalChecked(), IsCompleteGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("package").ToLocalChecked(), PackageGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("progress").ToLocalChecked(), ProgressGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageUninstallingEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageUninstallingEventArgs(::Windows::ApplicationModel::PackageUninstallingEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageUninstallingEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUninstallingEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageUninstallingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageUninstallingEventArgs *wrapperInstance = new PackageUninstallingEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUninstallingEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageUninstallingEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageUninstallingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageUninstallingEventArgs(winRtInstance));
    }


  



    static void ActivityIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUninstallingEventArgs^>(info.This()))
      {
        return;
      }

      PackageUninstallingEventArgs *wrapper = PackageUninstallingEventArgs::Unwrap<PackageUninstallingEventArgs>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->ActivityId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ErrorCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUninstallingEventArgs^>(info.This()))
      {
        return;
      }

      PackageUninstallingEventArgs *wrapper = PackageUninstallingEventArgs::Unwrap<PackageUninstallingEventArgs>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ErrorCode;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsCompleteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUninstallingEventArgs^>(info.This()))
      {
        return;
      }

      PackageUninstallingEventArgs *wrapper = PackageUninstallingEventArgs::Unwrap<PackageUninstallingEventArgs>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsComplete;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUninstallingEventArgs^>(info.This()))
      {
        return;
      }

      PackageUninstallingEventArgs *wrapper = PackageUninstallingEventArgs::Unwrap<PackageUninstallingEventArgs>(info.This());

      try 
      {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->Package;
        info.GetReturnValue().Set(WrapPackage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProgressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageUninstallingEventArgs^>(info.This()))
      {
        return;
      }

      PackageUninstallingEventArgs *wrapper = PackageUninstallingEventArgs::Unwrap<PackageUninstallingEventArgs>(info.This());

      try 
      {
        double result = wrapper->_instance->Progress;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageUninstallingEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageUninstallingEventArgs(::Windows::ApplicationModel::PackageUninstallingEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageUninstallingEventArgs^ UnwrapPackageUninstallingEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageUninstallingEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageUninstallingEventArgs(::Windows::ApplicationModel::PackageUninstallingEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageUninstallingEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageUninstallingEventArgs^ UnwrapPackageUninstallingEventArgs(Local<Value> value)
  {
     return PackageUninstallingEventArgs::Unwrap<PackageUninstallingEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageUninstallingEventArgs(Local<Object> exports)
  {
    PackageUninstallingEventArgs::Init(exports);
  }

  class PackageStatusChangedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageStatusChangedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("package").ToLocalChecked(), PackageGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageStatusChangedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageStatusChangedEventArgs(::Windows::ApplicationModel::PackageStatusChangedEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageStatusChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatusChangedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageStatusChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageStatusChangedEventArgs *wrapperInstance = new PackageStatusChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatusChangedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageStatusChangedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageStatusChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageStatusChangedEventArgs(winRtInstance));
    }


  



    static void PackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageStatusChangedEventArgs^>(info.This()))
      {
        return;
      }

      PackageStatusChangedEventArgs *wrapper = PackageStatusChangedEventArgs::Unwrap<PackageStatusChangedEventArgs>(info.This());

      try 
      {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->Package;
        info.GetReturnValue().Set(WrapPackage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageStatusChangedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageStatusChangedEventArgs(::Windows::ApplicationModel::PackageStatusChangedEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageStatusChangedEventArgs^ UnwrapPackageStatusChangedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageStatusChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageStatusChangedEventArgs(::Windows::ApplicationModel::PackageStatusChangedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageStatusChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageStatusChangedEventArgs^ UnwrapPackageStatusChangedEventArgs(Local<Value> value)
  {
     return PackageStatusChangedEventArgs::Unwrap<PackageStatusChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageStatusChangedEventArgs(Local<Object> exports)
  {
    PackageStatusChangedEventArgs::Init(exports);
  }

  class PackageContentGroupStagingEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageContentGroupStagingEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("activityId").ToLocalChecked(), ActivityIdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("contentGroupName").ToLocalChecked(), ContentGroupNameGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("errorCode").ToLocalChecked(), ErrorCodeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isComplete").ToLocalChecked(), IsCompleteGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isContentGroupRequired").ToLocalChecked(), IsContentGroupRequiredGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("package").ToLocalChecked(), PackageGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("progress").ToLocalChecked(), ProgressGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageContentGroupStagingEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageContentGroupStagingEventArgs(::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageContentGroupStagingEventArgs *wrapperInstance = new PackageContentGroupStagingEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageContentGroupStagingEventArgs(winRtInstance));
    }


  



    static void ActivityIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageContentGroupStagingEventArgs *wrapper = PackageContentGroupStagingEventArgs::Unwrap<PackageContentGroupStagingEventArgs>(info.This());

      try 
      {
        ::Platform::Guid result = wrapper->_instance->ActivityId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ContentGroupNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageContentGroupStagingEventArgs *wrapper = PackageContentGroupStagingEventArgs::Unwrap<PackageContentGroupStagingEventArgs>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->ContentGroupName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ErrorCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageContentGroupStagingEventArgs *wrapper = PackageContentGroupStagingEventArgs::Unwrap<PackageContentGroupStagingEventArgs>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ErrorCode;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsCompleteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageContentGroupStagingEventArgs *wrapper = PackageContentGroupStagingEventArgs::Unwrap<PackageContentGroupStagingEventArgs>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsComplete;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsContentGroupRequiredGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageContentGroupStagingEventArgs *wrapper = PackageContentGroupStagingEventArgs::Unwrap<PackageContentGroupStagingEventArgs>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsContentGroupRequired;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageContentGroupStagingEventArgs *wrapper = PackageContentGroupStagingEventArgs::Unwrap<PackageContentGroupStagingEventArgs>(info.This());

      try 
      {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->Package;
        info.GetReturnValue().Set(WrapPackage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ProgressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^>(info.This()))
      {
        return;
      }

      PackageContentGroupStagingEventArgs *wrapper = PackageContentGroupStagingEventArgs::Unwrap<PackageContentGroupStagingEventArgs>(info.This());

      try 
      {
        double result = wrapper->_instance->Progress;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageContentGroupStagingEventArgs(::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^ UnwrapPackageContentGroupStagingEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageContentGroupStagingEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageContentGroupStagingEventArgs(::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageContentGroupStagingEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^ UnwrapPackageContentGroupStagingEventArgs(Local<Value> value)
  {
     return PackageContentGroupStagingEventArgs::Unwrap<PackageContentGroupStagingEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageContentGroupStagingEventArgs(Local<Object> exports)
  {
    PackageContentGroupStagingEventArgs::Init(exports);
  }

  class PackageCatalog : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageCatalog").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "addOptionalPackageAsync", AddOptionalPackageAsync);
      Nan::SetPrototypeMethod(localRef, "removeOptionalPackagesAsync", RemoveOptionalPackagesAsync);
      Nan::SetPrototypeMethod(localRef, "addResourcePackageAsync", AddResourcePackageAsync);
      Nan::SetPrototypeMethod(localRef, "removeResourcePackagesAsync", RemoveResourcePackagesAsync);
      
            
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "openForCurrentPackage", OpenForCurrentPackage);
      Nan::SetMethod(constructor, "openForCurrentUser", OpenForCurrentUser);

      Nan::Set(exports, Nan::New<String>("PackageCatalog").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageCatalog(::Windows::ApplicationModel::PackageCatalog^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageCatalog^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageCatalog^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageCatalog *wrapperInstance = new PackageCatalog(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageCatalog^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageCatalog^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageCatalog(winRtInstance));
    }


    static void AddOptionalPackageAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^>^ op;
    

      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          op = wrapper->_instance->AddOptionalPackageAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapPackageCatalogAddOptionalPackageResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void RemoveOptionalPackagesAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^>^ op;
    

      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->RemoveOptionalPackagesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapPackageCatalogRemoveOptionalPackagesResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void AddResourcePackageAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^, ::Windows::ApplicationModel::PackageInstallProgress>^ op;
    

      if (info.Length() == 4
        && info[0]->IsString()
        && info[1]->IsString()
        && info[2]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          ::Windows::ApplicationModel::AddResourcePackageOptions arg2 = static_cast<::Windows::ApplicationModel::AddResourcePackageOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->AddResourcePackageAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapPackageCatalogAddResourcePackageResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
    static void RemoveResourcePackagesAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^>^ op;
    

      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::ApplicationModel::Package^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::ApplicationModel::Package^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::ApplicationModel::Package^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::ApplicationModel::Package^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::ApplicationModel::Package^ {
                   return UnwrapPackage(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::ApplicationModel::Package^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->RemoveResourcePackagesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    
      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapPackageCatalogRemoveResourcePackagesResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else 
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
             
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);
        
            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }  		
      });
    }
  


    static void OpenForCurrentPackage(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::ApplicationModel::PackageCatalog^ result;
          result = ::Windows::ApplicationModel::PackageCatalog::OpenForCurrentPackage();
          info.GetReturnValue().Set(WrapPackageCatalog(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void OpenForCurrentUser(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::ApplicationModel::PackageCatalog^ result;
          result = ::Windows::ApplicationModel::PackageCatalog::OpenForCurrentUser();
          info.GetReturnValue().Set(WrapPackageCatalog(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
		return;
      }

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"packageInstalling", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PackageInstalling::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::ApplicationModel::PackageCatalog^, ::Windows::ApplicationModel::PackageInstallingEventArgs^>(
            [callbackObjPtr](::Windows::ApplicationModel::PackageCatalog^ arg0, ::Windows::ApplicationModel::PackageInstallingEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapPackageCatalog(arg0);
                  wrappedArg1 = WrapPackageInstallingEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"packageStaging", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PackageStaging::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::ApplicationModel::PackageCatalog^, ::Windows::ApplicationModel::PackageStagingEventArgs^>(
            [callbackObjPtr](::Windows::ApplicationModel::PackageCatalog^ arg0, ::Windows::ApplicationModel::PackageStagingEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapPackageCatalog(arg0);
                  wrappedArg1 = WrapPackageStagingEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"packageStatusChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PackageStatusChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::ApplicationModel::PackageCatalog^, ::Windows::ApplicationModel::PackageStatusChangedEventArgs^>(
            [callbackObjPtr](::Windows::ApplicationModel::PackageCatalog^ arg0, ::Windows::ApplicationModel::PackageStatusChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapPackageCatalog(arg0);
                  wrappedArg1 = WrapPackageStatusChangedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"packageUninstalling", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PackageUninstalling::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::ApplicationModel::PackageCatalog^, ::Windows::ApplicationModel::PackageUninstallingEventArgs^>(
            [callbackObjPtr](::Windows::ApplicationModel::PackageCatalog^ arg0, ::Windows::ApplicationModel::PackageUninstallingEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapPackageCatalog(arg0);
                  wrappedArg1 = WrapPackageUninstallingEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"packageUpdating", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PackageUpdating::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::ApplicationModel::PackageCatalog^, ::Windows::ApplicationModel::PackageUpdatingEventArgs^>(
            [callbackObjPtr](::Windows::ApplicationModel::PackageCatalog^ arg0, ::Windows::ApplicationModel::PackageUpdatingEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapPackageCatalog(arg0);
                  wrappedArg1 = WrapPackageUpdatingEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"packageContentGroupStaging", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PackageContentGroupStaging::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::ApplicationModel::PackageCatalog^, ::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^>(
            [callbackObjPtr](::Windows::ApplicationModel::PackageCatalog^ arg0, ::Windows::ApplicationModel::PackageContentGroupStagingEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapPackageCatalog(arg0);
                  wrappedArg1 = WrapPackageContentGroupStagingEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else 
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
		return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false))
      {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      }
      else
      {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"packageInstalling", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"packageStaging", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"packageStatusChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"packageUninstalling", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"packageUpdating", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"packageContentGroupStaging", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
                
      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false))
      {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false))
      {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());
            
      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;
        
      try 
      {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"packageInstalling", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
          wrapper->_instance->PackageInstalling::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"packageStaging", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
          wrapper->_instance->PackageStaging::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"packageStatusChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
          wrapper->_instance->PackageStatusChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"packageUninstalling", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
          wrapper->_instance->PackageUninstalling::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"packageUpdating", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
          wrapper->_instance->PackageUpdating::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"packageContentGroupStaging", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalog^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          PackageCatalog *wrapper = PackageCatalog::Unwrap<PackageCatalog>(info.This());
          wrapper->_instance->PackageContentGroupStaging::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::ApplicationModel::PackageCatalog^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageCatalog(::Windows::ApplicationModel::PackageCatalog^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageCatalog^ UnwrapPackageCatalog(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageCatalog::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageCatalog(::Windows::ApplicationModel::PackageCatalog^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageCatalog::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageCatalog^ UnwrapPackageCatalog(Local<Value> value)
  {
     return PackageCatalog::Unwrap<PackageCatalog>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageCatalog(Local<Object> exports)
  {
    PackageCatalog::Init(exports);
  }

  class PackageCatalogAddOptionalPackageResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageCatalogAddOptionalPackageResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("package").ToLocalChecked(), PackageGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageCatalogAddOptionalPackageResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageCatalogAddOptionalPackageResult(::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageCatalogAddOptionalPackageResult *wrapperInstance = new PackageCatalogAddOptionalPackageResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageCatalogAddOptionalPackageResult(winRtInstance));
    }


  



    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^>(info.This()))
      {
        return;
      }

      PackageCatalogAddOptionalPackageResult *wrapper = PackageCatalogAddOptionalPackageResult::Unwrap<PackageCatalogAddOptionalPackageResult>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^>(info.This()))
      {
        return;
      }

      PackageCatalogAddOptionalPackageResult *wrapper = PackageCatalogAddOptionalPackageResult::Unwrap<PackageCatalogAddOptionalPackageResult>(info.This());

      try 
      {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->Package;
        info.GetReturnValue().Set(WrapPackage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageCatalogAddOptionalPackageResult(::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^ UnwrapPackageCatalogAddOptionalPackageResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageCatalogAddOptionalPackageResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageCatalogAddOptionalPackageResult(::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageCatalogAddOptionalPackageResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageCatalogAddOptionalPackageResult^ UnwrapPackageCatalogAddOptionalPackageResult(Local<Value> value)
  {
     return PackageCatalogAddOptionalPackageResult::Unwrap<PackageCatalogAddOptionalPackageResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageCatalogAddOptionalPackageResult(Local<Object> exports)
  {
    PackageCatalogAddOptionalPackageResult::Init(exports);
  }

  class PackageCatalogRemoveOptionalPackagesResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageCatalogRemoveOptionalPackagesResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("packagesRemoved").ToLocalChecked(), PackagesRemovedGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageCatalogRemoveOptionalPackagesResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageCatalogRemoveOptionalPackagesResult(::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageCatalogRemoveOptionalPackagesResult *wrapperInstance = new PackageCatalogRemoveOptionalPackagesResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageCatalogRemoveOptionalPackagesResult(winRtInstance));
    }


  



    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^>(info.This()))
      {
        return;
      }

      PackageCatalogRemoveOptionalPackagesResult *wrapper = PackageCatalogRemoveOptionalPackagesResult::Unwrap<PackageCatalogRemoveOptionalPackagesResult>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PackagesRemovedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^>(info.This()))
      {
        return;
      }

      PackageCatalogRemoveOptionalPackagesResult *wrapper = PackageCatalogRemoveOptionalPackagesResult::Unwrap<PackageCatalogRemoveOptionalPackagesResult>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::ApplicationModel::Package^>^ result = wrapper->_instance->PackagesRemoved;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::ApplicationModel::Package^>::CreateVectorViewWrapper(result, 
            [](::Windows::ApplicationModel::Package^ val) -> Local<Value> {
              return WrapPackage(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(value);
            },
            [](Local<Value> value) -> ::Windows::ApplicationModel::Package^ {
              return UnwrapPackage(value);
            }
          ));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageCatalogRemoveOptionalPackagesResult(::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^ UnwrapPackageCatalogRemoveOptionalPackagesResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageCatalogRemoveOptionalPackagesResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageCatalogRemoveOptionalPackagesResult(::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageCatalogRemoveOptionalPackagesResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageCatalogRemoveOptionalPackagesResult^ UnwrapPackageCatalogRemoveOptionalPackagesResult(Local<Value> value)
  {
     return PackageCatalogRemoveOptionalPackagesResult::Unwrap<PackageCatalogRemoveOptionalPackagesResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageCatalogRemoveOptionalPackagesResult(Local<Object> exports)
  {
    PackageCatalogRemoveOptionalPackagesResult::Init(exports);
  }

  class PackageCatalogRemoveResourcePackagesResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageCatalogRemoveResourcePackagesResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("packagesRemoved").ToLocalChecked(), PackagesRemovedGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageCatalogRemoveResourcePackagesResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageCatalogRemoveResourcePackagesResult(::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageCatalogRemoveResourcePackagesResult *wrapperInstance = new PackageCatalogRemoveResourcePackagesResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageCatalogRemoveResourcePackagesResult(winRtInstance));
    }


  



    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^>(info.This()))
      {
        return;
      }

      PackageCatalogRemoveResourcePackagesResult *wrapper = PackageCatalogRemoveResourcePackagesResult::Unwrap<PackageCatalogRemoveResourcePackagesResult>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PackagesRemovedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^>(info.This()))
      {
        return;
      }

      PackageCatalogRemoveResourcePackagesResult *wrapper = PackageCatalogRemoveResourcePackagesResult::Unwrap<PackageCatalogRemoveResourcePackagesResult>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::ApplicationModel::Package^>^ result = wrapper->_instance->PackagesRemoved;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::ApplicationModel::Package^>::CreateVectorViewWrapper(result, 
            [](::Windows::ApplicationModel::Package^ val) -> Local<Value> {
              return WrapPackage(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::Package^>(value);
            },
            [](Local<Value> value) -> ::Windows::ApplicationModel::Package^ {
              return UnwrapPackage(value);
            }
          ));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageCatalogRemoveResourcePackagesResult(::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^ UnwrapPackageCatalogRemoveResourcePackagesResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageCatalogRemoveResourcePackagesResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageCatalogRemoveResourcePackagesResult(::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageCatalogRemoveResourcePackagesResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageCatalogRemoveResourcePackagesResult^ UnwrapPackageCatalogRemoveResourcePackagesResult(Local<Value> value)
  {
     return PackageCatalogRemoveResourcePackagesResult::Unwrap<PackageCatalogRemoveResourcePackagesResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageCatalogRemoveResourcePackagesResult(Local<Object> exports)
  {
    PackageCatalogRemoveResourcePackagesResult::Init(exports);
  }

  class PackageCatalogAddResourcePackageResult : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("PackageCatalogAddResourcePackageResult").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isComplete").ToLocalChecked(), IsCompleteGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("package").ToLocalChecked(), PackageGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("PackageCatalogAddResourcePackageResult").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    PackageCatalogAddResourcePackageResult(::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PackageCatalogAddResourcePackageResult *wrapperInstance = new PackageCatalogAddResourcePackageResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapPackageCatalogAddResourcePackageResult(winRtInstance));
    }


  



    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^>(info.This()))
      {
        return;
      }

      PackageCatalogAddResourcePackageResult *wrapper = PackageCatalogAddResourcePackageResult::Unwrap<PackageCatalogAddResourcePackageResult>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IsCompleteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^>(info.This()))
      {
        return;
      }

      PackageCatalogAddResourcePackageResult *wrapper = PackageCatalogAddResourcePackageResult::Unwrap<PackageCatalogAddResourcePackageResult>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsComplete;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PackageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^>(info.This()))
      {
        return;
      }

      PackageCatalogAddResourcePackageResult *wrapper = PackageCatalogAddResourcePackageResult::Unwrap<PackageCatalogAddResourcePackageResult>(info.This());

      try 
      {
        ::Windows::ApplicationModel::Package^ result = wrapper->_instance->Package;
        info.GetReturnValue().Set(WrapPackage(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapPackageCatalogAddResourcePackageResult(::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^ wintRtInstance);
    friend ::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^ UnwrapPackageCatalogAddResourcePackageResult(Local<Value> value);
  };
  Persistent<FunctionTemplate> PackageCatalogAddResourcePackageResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapPackageCatalogAddResourcePackageResult(::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PackageCatalogAddResourcePackageResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::PackageCatalogAddResourcePackageResult^ UnwrapPackageCatalogAddResourcePackageResult(Local<Value> value)
  {
     return PackageCatalogAddResourcePackageResult::Unwrap<PackageCatalogAddResourcePackageResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPackageCatalogAddResourcePackageResult(Local<Object> exports)
  {
    PackageCatalogAddResourcePackageResult::Init(exports);
  }

  class DesignMode : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("DesignMode").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetAccessor(constructor, Nan::New<String>("designModeEnabled").ToLocalChecked(), DesignModeEnabledGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("designMode2Enabled").ToLocalChecked(), DesignMode2EnabledGetter);

      Nan::Set(exports, Nan::New<String>("DesignMode").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    DesignMode(::Windows::ApplicationModel::DesignMode^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::DesignMode^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::DesignMode^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::DesignMode^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      DesignMode *wrapperInstance = new DesignMode(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::DesignMode^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::DesignMode^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::DesignMode^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapDesignMode(winRtInstance));
    }


  




    static void DesignModeEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        bool result = ::Windows::ApplicationModel::DesignMode::DesignModeEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DesignMode2EnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        bool result = ::Windows::ApplicationModel::DesignMode::DesignMode2Enabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

  private:
    ::Windows::ApplicationModel::DesignMode^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapDesignMode(::Windows::ApplicationModel::DesignMode^ wintRtInstance);
    friend ::Windows::ApplicationModel::DesignMode^ UnwrapDesignMode(Local<Value> value);
  };
  Persistent<FunctionTemplate> DesignMode::s_constructorTemplate;

  v8::Local<v8::Value> WrapDesignMode(::Windows::ApplicationModel::DesignMode^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DesignMode::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::DesignMode^ UnwrapDesignMode(Local<Value> value)
  {
     return DesignMode::Unwrap<DesignMode>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDesignMode(Local<Object> exports)
  {
    DesignMode::Init(exports);
  }

  class AppInstance : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("AppInstance").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "redirectActivationTo", RedirectActivationTo);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isCurrentInstance").ToLocalChecked(), IsCurrentInstanceGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("key").ToLocalChecked(), KeyGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "getActivatedEventArgs", GetActivatedEventArgs);
      Nan::SetMethod(constructor, "findOrRegisterInstanceForKey", FindOrRegisterInstanceForKey);
      Nan::SetMethod(constructor, "unregister", Unregister);
      Nan::SetMethod(constructor, "getInstances", GetInstances);
      Nan::SetAccessor(constructor, Nan::New<String>("recommendedInstance").ToLocalChecked(), RecommendedInstanceGetter);

      Nan::Set(exports, Nan::New<String>("AppInstance").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    AppInstance(::Windows::ApplicationModel::AppInstance^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::AppInstance^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInstance^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::AppInstance^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      AppInstance *wrapperInstance = new AppInstance(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInstance^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::AppInstance^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::AppInstance^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapAppInstance(winRtInstance));
    }


  
    static void RedirectActivationTo(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInstance^>(info.This()))
      {
        return;
      }

      AppInstance *wrapper = AppInstance::Unwrap<AppInstance>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->RedirectActivationTo();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }


    static void GetActivatedEventArgs(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::ApplicationModel::Activation::IActivatedEventArgs^ result;
          result = ::Windows::ApplicationModel::AppInstance::GetActivatedEventArgs();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.ApplicationModel.Activation", "IActivatedEventArgs", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void FindOrRegisterInstanceForKey(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::ApplicationModel::AppInstance^ result;
          result = ::Windows::ApplicationModel::AppInstance::FindOrRegisterInstanceForKey(arg0);
          info.GetReturnValue().Set(WrapAppInstance(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Unregister(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::ApplicationModel::AppInstance::Unregister();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetInstances(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVector<::Windows::ApplicationModel::AppInstance^>^ result;
          result = ::Windows::ApplicationModel::AppInstance::GetInstances();
          info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Windows::ApplicationModel::AppInstance^>::CreateVectorWrapper(result, 
            [](::Windows::ApplicationModel::AppInstance^ val) -> Local<Value> {
              return WrapAppInstance(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInstance^>(value);
            },
            [](Local<Value> value) -> ::Windows::ApplicationModel::AppInstance^ {
              return UnwrapAppInstance(value);
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void IsCurrentInstanceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInstance^>(info.This()))
      {
        return;
      }

      AppInstance *wrapper = AppInstance::Unwrap<AppInstance>(info.This());

      try 
      {
        bool result = wrapper->_instance->IsCurrentInstance;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void KeyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::AppInstance^>(info.This()))
      {
        return;
      }

      AppInstance *wrapper = AppInstance::Unwrap<AppInstance>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Key;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

    static void RecommendedInstanceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Windows::ApplicationModel::AppInstance^ result = ::Windows::ApplicationModel::AppInstance::RecommendedInstance;
        info.GetReturnValue().Set(WrapAppInstance(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

  private:
    ::Windows::ApplicationModel::AppInstance^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapAppInstance(::Windows::ApplicationModel::AppInstance^ wintRtInstance);
    friend ::Windows::ApplicationModel::AppInstance^ UnwrapAppInstance(Local<Value> value);
  };
  Persistent<FunctionTemplate> AppInstance::s_constructorTemplate;

  v8::Local<v8::Value> WrapAppInstance(::Windows::ApplicationModel::AppInstance^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(AppInstance::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::AppInstance^ UnwrapAppInstance(Local<Value> value)
  {
     return AppInstance::Unwrap<AppInstance>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitAppInstance(Local<Object> exports)
  {
    AppInstance::Init(exports);
  }

  class SuspendingEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("SuspendingEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("suspendingOperation").ToLocalChecked(), SuspendingOperationGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("SuspendingEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    SuspendingEventArgs(::Windows::ApplicationModel::SuspendingEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::SuspendingEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::SuspendingEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::SuspendingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SuspendingEventArgs *wrapperInstance = new SuspendingEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::SuspendingEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::SuspendingEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::SuspendingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapSuspendingEventArgs(winRtInstance));
    }


  



    static void SuspendingOperationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::SuspendingEventArgs^>(info.This()))
      {
        return;
      }

      SuspendingEventArgs *wrapper = SuspendingEventArgs::Unwrap<SuspendingEventArgs>(info.This());

      try 
      {
        ::Windows::ApplicationModel::SuspendingOperation^ result = wrapper->_instance->SuspendingOperation;
        info.GetReturnValue().Set(WrapSuspendingOperation(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::SuspendingEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapSuspendingEventArgs(::Windows::ApplicationModel::SuspendingEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::SuspendingEventArgs^ UnwrapSuspendingEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> SuspendingEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapSuspendingEventArgs(::Windows::ApplicationModel::SuspendingEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SuspendingEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::SuspendingEventArgs^ UnwrapSuspendingEventArgs(Local<Value> value)
  {
     return SuspendingEventArgs::Unwrap<SuspendingEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSuspendingEventArgs(Local<Object> exports)
  {
    SuspendingEventArgs::Init(exports);
  }

  class LeavingBackgroundEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("LeavingBackgroundEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("LeavingBackgroundEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    LeavingBackgroundEventArgs(::Windows::ApplicationModel::LeavingBackgroundEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::LeavingBackgroundEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::LeavingBackgroundEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::LeavingBackgroundEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      LeavingBackgroundEventArgs *wrapperInstance = new LeavingBackgroundEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::LeavingBackgroundEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::LeavingBackgroundEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::LeavingBackgroundEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapLeavingBackgroundEventArgs(winRtInstance));
    }


  
    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::LeavingBackgroundEventArgs^>(info.This()))
      {
        return;
      }

      LeavingBackgroundEventArgs *wrapper = LeavingBackgroundEventArgs::Unwrap<LeavingBackgroundEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





  private:
    ::Windows::ApplicationModel::LeavingBackgroundEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapLeavingBackgroundEventArgs(::Windows::ApplicationModel::LeavingBackgroundEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::LeavingBackgroundEventArgs^ UnwrapLeavingBackgroundEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> LeavingBackgroundEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapLeavingBackgroundEventArgs(::Windows::ApplicationModel::LeavingBackgroundEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(LeavingBackgroundEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::LeavingBackgroundEventArgs^ UnwrapLeavingBackgroundEventArgs(Local<Value> value)
  {
     return LeavingBackgroundEventArgs::Unwrap<LeavingBackgroundEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitLeavingBackgroundEventArgs(Local<Object> exports)
  {
    LeavingBackgroundEventArgs::Init(exports);
  }

  class EnteredBackgroundEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("EnteredBackgroundEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("EnteredBackgroundEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    EnteredBackgroundEventArgs(::Windows::ApplicationModel::EnteredBackgroundEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::EnteredBackgroundEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::EnteredBackgroundEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::EnteredBackgroundEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      EnteredBackgroundEventArgs *wrapperInstance = new EnteredBackgroundEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::EnteredBackgroundEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::EnteredBackgroundEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::EnteredBackgroundEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapEnteredBackgroundEventArgs(winRtInstance));
    }


  
    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::EnteredBackgroundEventArgs^>(info.This()))
      {
        return;
      }

      EnteredBackgroundEventArgs *wrapper = EnteredBackgroundEventArgs::Unwrap<EnteredBackgroundEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





  private:
    ::Windows::ApplicationModel::EnteredBackgroundEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapEnteredBackgroundEventArgs(::Windows::ApplicationModel::EnteredBackgroundEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::EnteredBackgroundEventArgs^ UnwrapEnteredBackgroundEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> EnteredBackgroundEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapEnteredBackgroundEventArgs(::Windows::ApplicationModel::EnteredBackgroundEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(EnteredBackgroundEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::EnteredBackgroundEventArgs^ UnwrapEnteredBackgroundEventArgs(Local<Value> value)
  {
     return EnteredBackgroundEventArgs::Unwrap<EnteredBackgroundEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitEnteredBackgroundEventArgs(Local<Object> exports)
  {
    EnteredBackgroundEventArgs::Init(exports);
  }

  class ISuspendingDeferral : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ISuspendingDeferral").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "complete", Complete);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("ISuspendingDeferral").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ISuspendingDeferral(::Windows::ApplicationModel::ISuspendingDeferral^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::ISuspendingDeferral^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ISuspendingDeferral^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::ISuspendingDeferral^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ISuspendingDeferral *wrapperInstance = new ISuspendingDeferral(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ISuspendingDeferral^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::ISuspendingDeferral^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::ISuspendingDeferral^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapISuspendingDeferral(winRtInstance));
    }


  
    static void Complete(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ISuspendingDeferral^>(info.This()))
      {
        return;
      }

      ISuspendingDeferral *wrapper = ISuspendingDeferral::Unwrap<ISuspendingDeferral>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Complete();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





  private:
    ::Windows::ApplicationModel::ISuspendingDeferral^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapISuspendingDeferral(::Windows::ApplicationModel::ISuspendingDeferral^ wintRtInstance);
    friend ::Windows::ApplicationModel::ISuspendingDeferral^ UnwrapISuspendingDeferral(Local<Value> value);
  };
  Persistent<FunctionTemplate> ISuspendingDeferral::s_constructorTemplate;

  v8::Local<v8::Value> WrapISuspendingDeferral(::Windows::ApplicationModel::ISuspendingDeferral^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ISuspendingDeferral::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::ISuspendingDeferral^ UnwrapISuspendingDeferral(Local<Value> value)
  {
     return ISuspendingDeferral::Unwrap<ISuspendingDeferral>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitISuspendingDeferral(Local<Object> exports)
  {
    ISuspendingDeferral::Init(exports);
  }

  class SuspendingDeferral : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("SuspendingDeferral").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "complete", Complete);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("SuspendingDeferral").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    SuspendingDeferral(::Windows::ApplicationModel::SuspendingDeferral^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::SuspendingDeferral^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::SuspendingDeferral^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::SuspendingDeferral^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SuspendingDeferral *wrapperInstance = new SuspendingDeferral(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::SuspendingDeferral^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::SuspendingDeferral^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::SuspendingDeferral^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapSuspendingDeferral(winRtInstance));
    }


  
    static void Complete(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::SuspendingDeferral^>(info.This()))
      {
        return;
      }

      SuspendingDeferral *wrapper = SuspendingDeferral::Unwrap<SuspendingDeferral>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Complete();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





  private:
    ::Windows::ApplicationModel::SuspendingDeferral^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapSuspendingDeferral(::Windows::ApplicationModel::SuspendingDeferral^ wintRtInstance);
    friend ::Windows::ApplicationModel::SuspendingDeferral^ UnwrapSuspendingDeferral(Local<Value> value);
  };
  Persistent<FunctionTemplate> SuspendingDeferral::s_constructorTemplate;

  v8::Local<v8::Value> WrapSuspendingDeferral(::Windows::ApplicationModel::SuspendingDeferral^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SuspendingDeferral::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::SuspendingDeferral^ UnwrapSuspendingDeferral(Local<Value> value)
  {
     return SuspendingDeferral::Unwrap<SuspendingDeferral>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSuspendingDeferral(Local<Object> exports)
  {
    SuspendingDeferral::Init(exports);
  }

  class ISuspendingOperation : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ISuspendingOperation").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deadline").ToLocalChecked(), DeadlineGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("ISuspendingOperation").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ISuspendingOperation(::Windows::ApplicationModel::ISuspendingOperation^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::ISuspendingOperation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ISuspendingOperation^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::ISuspendingOperation^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ISuspendingOperation *wrapperInstance = new ISuspendingOperation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ISuspendingOperation^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::ISuspendingOperation^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::ISuspendingOperation^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapISuspendingOperation(winRtInstance));
    }


  
    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ISuspendingOperation^>(info.This()))
      {
        return;
      }

      ISuspendingOperation *wrapper = ISuspendingOperation::Unwrap<ISuspendingOperation>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::ApplicationModel::SuspendingDeferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(WrapSuspendingDeferral(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void DeadlineGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ISuspendingOperation^>(info.This()))
      {
        return;
      }

      ISuspendingOperation *wrapper = ISuspendingOperation::Unwrap<ISuspendingOperation>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->Deadline;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::ISuspendingOperation^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapISuspendingOperation(::Windows::ApplicationModel::ISuspendingOperation^ wintRtInstance);
    friend ::Windows::ApplicationModel::ISuspendingOperation^ UnwrapISuspendingOperation(Local<Value> value);
  };
  Persistent<FunctionTemplate> ISuspendingOperation::s_constructorTemplate;

  v8::Local<v8::Value> WrapISuspendingOperation(::Windows::ApplicationModel::ISuspendingOperation^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ISuspendingOperation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::ISuspendingOperation^ UnwrapISuspendingOperation(Local<Value> value)
  {
     return ISuspendingOperation::Unwrap<ISuspendingOperation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitISuspendingOperation(Local<Object> exports)
  {
    ISuspendingOperation::Init(exports);
  }

  class SuspendingOperation : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("SuspendingOperation").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deadline").ToLocalChecked(), DeadlineGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("SuspendingOperation").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    SuspendingOperation(::Windows::ApplicationModel::SuspendingOperation^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::SuspendingOperation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::SuspendingOperation^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::SuspendingOperation^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SuspendingOperation *wrapperInstance = new SuspendingOperation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::SuspendingOperation^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::SuspendingOperation^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::SuspendingOperation^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapSuspendingOperation(winRtInstance));
    }


  
    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::SuspendingOperation^>(info.This()))
      {
        return;
      }

      SuspendingOperation *wrapper = SuspendingOperation::Unwrap<SuspendingOperation>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::ApplicationModel::SuspendingDeferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(WrapSuspendingDeferral(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void DeadlineGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::SuspendingOperation^>(info.This()))
      {
        return;
      }

      SuspendingOperation *wrapper = SuspendingOperation::Unwrap<SuspendingOperation>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->Deadline;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::SuspendingOperation^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapSuspendingOperation(::Windows::ApplicationModel::SuspendingOperation^ wintRtInstance);
    friend ::Windows::ApplicationModel::SuspendingOperation^ UnwrapSuspendingOperation(Local<Value> value);
  };
  Persistent<FunctionTemplate> SuspendingOperation::s_constructorTemplate;

  v8::Local<v8::Value> WrapSuspendingOperation(::Windows::ApplicationModel::SuspendingOperation^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SuspendingOperation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::SuspendingOperation^ UnwrapSuspendingOperation(Local<Value> value)
  {
     return SuspendingOperation::Unwrap<SuspendingOperation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSuspendingOperation(Local<Object> exports)
  {
    SuspendingOperation::Init(exports);
  }

  class ISuspendingEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ISuspendingEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("suspendingOperation").ToLocalChecked(), SuspendingOperationGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("ISuspendingEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ISuspendingEventArgs(::Windows::ApplicationModel::ISuspendingEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::ISuspendingEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ISuspendingEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::ISuspendingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ISuspendingEventArgs *wrapperInstance = new ISuspendingEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ISuspendingEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::ISuspendingEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::ISuspendingEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapISuspendingEventArgs(winRtInstance));
    }


  



    static void SuspendingOperationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ISuspendingEventArgs^>(info.This()))
      {
        return;
      }

      ISuspendingEventArgs *wrapper = ISuspendingEventArgs::Unwrap<ISuspendingEventArgs>(info.This());

      try 
      {
        ::Windows::ApplicationModel::SuspendingOperation^ result = wrapper->_instance->SuspendingOperation;
        info.GetReturnValue().Set(WrapSuspendingOperation(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::ApplicationModel::ISuspendingEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapISuspendingEventArgs(::Windows::ApplicationModel::ISuspendingEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::ISuspendingEventArgs^ UnwrapISuspendingEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> ISuspendingEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapISuspendingEventArgs(::Windows::ApplicationModel::ISuspendingEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ISuspendingEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::ISuspendingEventArgs^ UnwrapISuspendingEventArgs(Local<Value> value)
  {
     return ISuspendingEventArgs::Unwrap<ISuspendingEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitISuspendingEventArgs(Local<Object> exports)
  {
    ISuspendingEventArgs::Init(exports);
  }

  class ILeavingBackgroundEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ILeavingBackgroundEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("ILeavingBackgroundEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ILeavingBackgroundEventArgs(::Windows::ApplicationModel::ILeavingBackgroundEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::ILeavingBackgroundEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ILeavingBackgroundEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::ILeavingBackgroundEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ILeavingBackgroundEventArgs *wrapperInstance = new ILeavingBackgroundEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ILeavingBackgroundEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::ILeavingBackgroundEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::ILeavingBackgroundEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapILeavingBackgroundEventArgs(winRtInstance));
    }


  
    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::ILeavingBackgroundEventArgs^>(info.This()))
      {
        return;
      }

      ILeavingBackgroundEventArgs *wrapper = ILeavingBackgroundEventArgs::Unwrap<ILeavingBackgroundEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





  private:
    ::Windows::ApplicationModel::ILeavingBackgroundEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapILeavingBackgroundEventArgs(::Windows::ApplicationModel::ILeavingBackgroundEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::ILeavingBackgroundEventArgs^ UnwrapILeavingBackgroundEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> ILeavingBackgroundEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapILeavingBackgroundEventArgs(::Windows::ApplicationModel::ILeavingBackgroundEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ILeavingBackgroundEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::ILeavingBackgroundEventArgs^ UnwrapILeavingBackgroundEventArgs(Local<Value> value)
  {
     return ILeavingBackgroundEventArgs::Unwrap<ILeavingBackgroundEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitILeavingBackgroundEventArgs(Local<Object> exports)
  {
    ILeavingBackgroundEventArgs::Init(exports);
  }

  class IEnteredBackgroundEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IEnteredBackgroundEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("IEnteredBackgroundEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IEnteredBackgroundEventArgs(::Windows::ApplicationModel::IEnteredBackgroundEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::IEnteredBackgroundEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::IEnteredBackgroundEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::IEnteredBackgroundEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IEnteredBackgroundEventArgs *wrapperInstance = new IEnteredBackgroundEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::IEnteredBackgroundEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::IEnteredBackgroundEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::IEnteredBackgroundEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapIEnteredBackgroundEventArgs(winRtInstance));
    }


  
    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::IEnteredBackgroundEventArgs^>(info.This()))
      {
        return;
      }

      IEnteredBackgroundEventArgs *wrapper = IEnteredBackgroundEventArgs::Unwrap<IEnteredBackgroundEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





  private:
    ::Windows::ApplicationModel::IEnteredBackgroundEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIEnteredBackgroundEventArgs(::Windows::ApplicationModel::IEnteredBackgroundEventArgs^ wintRtInstance);
    friend ::Windows::ApplicationModel::IEnteredBackgroundEventArgs^ UnwrapIEnteredBackgroundEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> IEnteredBackgroundEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapIEnteredBackgroundEventArgs(::Windows::ApplicationModel::IEnteredBackgroundEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IEnteredBackgroundEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::IEnteredBackgroundEventArgs^ UnwrapIEnteredBackgroundEventArgs(Local<Value> value)
  {
     return IEnteredBackgroundEventArgs::Unwrap<IEnteredBackgroundEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIEnteredBackgroundEventArgs(Local<Object> exports)
  {
    IEnteredBackgroundEventArgs::Init(exports);
  }

  class CameraApplicationManager : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("CameraApplicationManager").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "showInstalledApplicationsUI", ShowInstalledApplicationsUI);

      Nan::Set(exports, Nan::New<String>("CameraApplicationManager").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    CameraApplicationManager(::Windows::ApplicationModel::CameraApplicationManager^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
		  if (res.IsEmpty())
		  {
			  return;
		  }
		  info.GetReturnValue().Set(res.ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::ApplicationModel::CameraApplicationManager^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::CameraApplicationManager^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::ApplicationModel::CameraApplicationManager^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      CameraApplicationManager *wrapperInstance = new CameraApplicationManager(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::ApplicationModel::CameraApplicationManager^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::ApplicationModel::CameraApplicationManager^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::ApplicationModel::CameraApplicationManager^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapCameraApplicationManager(winRtInstance));
    }


  


    static void ShowInstalledApplicationsUI(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::ApplicationModel::CameraApplicationManager::ShowInstalledApplicationsUI();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



  private:
    ::Windows::ApplicationModel::CameraApplicationManager^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapCameraApplicationManager(::Windows::ApplicationModel::CameraApplicationManager^ wintRtInstance);
    friend ::Windows::ApplicationModel::CameraApplicationManager^ UnwrapCameraApplicationManager(Local<Value> value);
  };
  Persistent<FunctionTemplate> CameraApplicationManager::s_constructorTemplate;

  v8::Local<v8::Value> WrapCameraApplicationManager(::Windows::ApplicationModel::CameraApplicationManager^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(CameraApplicationManager::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::ApplicationModel::CameraApplicationManager^ UnwrapCameraApplicationManager(Local<Value> value)
  {
     return CameraApplicationManager::Unwrap<CameraApplicationManager>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitCameraApplicationManager(Local<Object> exports)
  {
    CameraApplicationManager::Init(exports);
  }

} } } 

NAN_MODULE_INIT(init)
{
  // we ignore failures for now since it probably means that the initialization already happened for STA, and that's cool
  CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  //if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
  /*{
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }*/
  
  NodeRT::Windows::ApplicationModel::InitStartupTaskStateEnum(target);
  NodeRT::Windows::ApplicationModel::InitPackageSignatureKindEnum(target);
  NodeRT::Windows::ApplicationModel::InitAddResourcePackageOptionsEnum(target);
  NodeRT::Windows::ApplicationModel::InitPackageContentGroupStateEnum(target);
  NodeRT::Windows::ApplicationModel::InitFullTrustProcessLauncher(target);
  NodeRT::Windows::ApplicationModel::InitStartupTask(target);
  NodeRT::Windows::ApplicationModel::InitAppDisplayInfo(target);
  NodeRT::Windows::ApplicationModel::InitAppInfo(target);
  NodeRT::Windows::ApplicationModel::InitPackageStatus(target);
  NodeRT::Windows::ApplicationModel::InitPackageId(target);
  NodeRT::Windows::ApplicationModel::InitPackage(target);
  NodeRT::Windows::ApplicationModel::InitPackageContentGroup(target);
  NodeRT::Windows::ApplicationModel::InitPackageStagingEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitPackageInstallingEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitPackageUpdatingEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitPackageUninstallingEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitPackageStatusChangedEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitPackageContentGroupStagingEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitPackageCatalog(target);
  NodeRT::Windows::ApplicationModel::InitPackageCatalogAddOptionalPackageResult(target);
  NodeRT::Windows::ApplicationModel::InitPackageCatalogRemoveOptionalPackagesResult(target);
  NodeRT::Windows::ApplicationModel::InitPackageCatalogRemoveResourcePackagesResult(target);
  NodeRT::Windows::ApplicationModel::InitPackageCatalogAddResourcePackageResult(target);
  NodeRT::Windows::ApplicationModel::InitDesignMode(target);
  NodeRT::Windows::ApplicationModel::InitAppInstance(target);
  NodeRT::Windows::ApplicationModel::InitSuspendingEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitLeavingBackgroundEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitEnteredBackgroundEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitISuspendingDeferral(target);
  NodeRT::Windows::ApplicationModel::InitSuspendingDeferral(target);
  NodeRT::Windows::ApplicationModel::InitISuspendingOperation(target);
  NodeRT::Windows::ApplicationModel::InitSuspendingOperation(target);
  NodeRT::Windows::ApplicationModel::InitISuspendingEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitILeavingBackgroundEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitIEnteredBackgroundEventArgs(target);
  NodeRT::Windows::ApplicationModel::InitCameraApplicationManager(target);

  NodeRT::Utils::RegisterNameSpace("Windows.ApplicationModel", target);
}


NODE_MODULE(binding, init)