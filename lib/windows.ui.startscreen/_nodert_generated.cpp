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

namespace NodeRT { namespace Windows { namespace UI { namespace StartScreen { 

  v8::Local<v8::Value> WrapJumpListItem(::Windows::UI::StartScreen::JumpListItem^ wintRtInstance);
  ::Windows::UI::StartScreen::JumpListItem^ UnwrapJumpListItem(Local<Value> value);
  
  v8::Local<v8::Value> WrapJumpList(::Windows::UI::StartScreen::JumpList^ wintRtInstance);
  ::Windows::UI::StartScreen::JumpList^ UnwrapJumpList(Local<Value> value);
  
  v8::Local<v8::Value> WrapSecondaryTileVisualElements(::Windows::UI::StartScreen::SecondaryTileVisualElements^ wintRtInstance);
  ::Windows::UI::StartScreen::SecondaryTileVisualElements^ UnwrapSecondaryTileVisualElements(Local<Value> value);
  
  v8::Local<v8::Value> WrapSecondaryTile(::Windows::UI::StartScreen::SecondaryTile^ wintRtInstance);
  ::Windows::UI::StartScreen::SecondaryTile^ UnwrapSecondaryTile(Local<Value> value);
  
  v8::Local<v8::Value> WrapVisualElementsRequestedEventArgs(::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^ wintRtInstance);
  ::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^ UnwrapVisualElementsRequestedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapVisualElementsRequest(::Windows::UI::StartScreen::VisualElementsRequest^ wintRtInstance);
  ::Windows::UI::StartScreen::VisualElementsRequest^ UnwrapVisualElementsRequest(Local<Value> value);
  
  v8::Local<v8::Value> WrapVisualElementsRequestDeferral(::Windows::UI::StartScreen::VisualElementsRequestDeferral^ wintRtInstance);
  ::Windows::UI::StartScreen::VisualElementsRequestDeferral^ UnwrapVisualElementsRequestDeferral(Local<Value> value);
  


  static void InitJumpListSystemGroupKindEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("JumpListSystemGroupKind").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::JumpListSystemGroupKind::None)));
	Nan::Set(enumObject, Nan::New<String>("frequent").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::JumpListSystemGroupKind::Frequent)));
	Nan::Set(enumObject, Nan::New<String>("recent").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::JumpListSystemGroupKind::Recent)));
  }


  static void InitJumpListItemKindEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("JumpListItemKind").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("arguments").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::JumpListItemKind::Arguments)));
	Nan::Set(enumObject, Nan::New<String>("separator").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::JumpListItemKind::Separator)));
  }


  static void InitTileOptionsEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("TileOptions").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileOptions::None)));
	Nan::Set(enumObject, Nan::New<String>("showNameOnLogo").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileOptions::ShowNameOnLogo)));
	Nan::Set(enumObject, Nan::New<String>("showNameOnWideLogo").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileOptions::ShowNameOnWideLogo)));
	Nan::Set(enumObject, Nan::New<String>("copyOnDeployment").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileOptions::CopyOnDeployment)));
  }


  static void InitTileSizeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("TileSize").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("default").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileSize::Default)));
	Nan::Set(enumObject, Nan::New<String>("square30x30").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileSize::Square30x30)));
	Nan::Set(enumObject, Nan::New<String>("square70x70").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileSize::Square70x70)));
	Nan::Set(enumObject, Nan::New<String>("square150x150").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileSize::Square150x150)));
	Nan::Set(enumObject, Nan::New<String>("wide310x150").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileSize::Wide310x150)));
	Nan::Set(enumObject, Nan::New<String>("square310x310").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileSize::Square310x310)));
	Nan::Set(enumObject, Nan::New<String>("square71x71").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileSize::Square71x71)));
	Nan::Set(enumObject, Nan::New<String>("square44x44").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::TileSize::Square44x44)));
  }


  static void InitForegroundTextEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("ForegroundText").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("dark").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::ForegroundText::Dark)));
	Nan::Set(enumObject, Nan::New<String>("light").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::StartScreen::ForegroundText::Light)));
  }



  
  static bool IsColorJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::UI::Color ColorFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::UI::Color returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> ColorToJsObject(::Windows::UI::Color value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    
    return scope.Escape(obj);
  }

  
  static bool IsPointJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Foundation::Point PointFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::Foundation::Point returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> PointToJsObject(::Windows::Foundation::Point value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    
    return scope.Escape(obj);
  }

  
  static bool IsRectJsObject(Local<Value> value)
  {
    if (!value->IsObject())
    {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Foundation::Rect RectFromJsObject(Local<Value> value)
  {
    HandleScope scope;
    ::Windows::Foundation::Rect returnValue;
    
    if (!value->IsObject())
    {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> RectToJsObject(::Windows::Foundation::Rect value)
  {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    
    return scope.Escape(obj);
  }

  
  class JumpListItem : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("JumpListItem").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("logo").ToLocalChecked(), LogoGetter, LogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("groupName").ToLocalChecked(), GroupNameGetter, GroupNameSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayName").ToLocalChecked(), DisplayNameGetter, DisplayNameSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("description").ToLocalChecked(), DescriptionGetter, DescriptionSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("arguments").ToLocalChecked(), ArgumentsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("kind").ToLocalChecked(), KindGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("removedByUser").ToLocalChecked(), RemovedByUserGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "createWithArguments", CreateWithArguments);
      Nan::SetMethod(constructor, "createSeparator", CreateSeparator);

      Nan::Set(exports, Nan::New<String>("JumpListItem").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    JumpListItem(::Windows::UI::StartScreen::JumpListItem^ instance)
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
      
      ::Windows::UI::StartScreen::JumpListItem^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::StartScreen::JumpListItem^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      JumpListItem *wrapperInstance = new JumpListItem(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::UI::StartScreen::JumpListItem^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::UI::StartScreen::JumpListItem^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapJumpListItem(winRtInstance));
    }


  


    static void CreateWithArguments(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 2
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          
          ::Windows::UI::StartScreen::JumpListItem^ result;
          result = ::Windows::UI::StartScreen::JumpListItem::CreateWithArguments(arg0, arg1);
          info.GetReturnValue().Set(WrapJumpListItem(result));
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
    static void CreateSeparator(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::UI::StartScreen::JumpListItem^ result;
          result = ::Windows::UI::StartScreen::JumpListItem::CreateSeparator();
          info.GetReturnValue().Set(WrapJumpListItem(result));
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

    static void LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info.This()))
      {
        return;
      }

      JumpListItem *wrapper = JumpListItem::Unwrap<JumpListItem>(info.This());

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
    
    static void LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info.This()))
      {
        return;
      }

      JumpListItem *wrapper = JumpListItem::Unwrap<JumpListItem>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void GroupNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info.This()))
      {
        return;
      }

      JumpListItem *wrapper = JumpListItem::Unwrap<JumpListItem>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->GroupName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GroupNameSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info.This()))
      {
        return;
      }

      JumpListItem *wrapper = JumpListItem::Unwrap<JumpListItem>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->GroupName = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void DisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info.This()))
      {
        return;
      }

      JumpListItem *wrapper = JumpListItem::Unwrap<JumpListItem>(info.This());

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
    
    static void DisplayNameSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info.This()))
      {
        return;
      }

      JumpListItem *wrapper = JumpListItem::Unwrap<JumpListItem>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->DisplayName = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void DescriptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info.This()))
      {
        return;
      }

      JumpListItem *wrapper = JumpListItem::Unwrap<JumpListItem>(info.This());

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
    
    static void DescriptionSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info.This()))
      {
        return;
      }

      JumpListItem *wrapper = JumpListItem::Unwrap<JumpListItem>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Description = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ArgumentsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info.This()))
      {
        return;
      }

      JumpListItem *wrapper = JumpListItem::Unwrap<JumpListItem>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Arguments;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void KindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info.This()))
      {
        return;
      }

      JumpListItem *wrapper = JumpListItem::Unwrap<JumpListItem>(info.This());

      try 
      {
        ::Windows::UI::StartScreen::JumpListItemKind result = wrapper->_instance->Kind;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RemovedByUserGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(info.This()))
      {
        return;
      }

      JumpListItem *wrapper = JumpListItem::Unwrap<JumpListItem>(info.This());

      try 
      {
        bool result = wrapper->_instance->RemovedByUser;
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
    ::Windows::UI::StartScreen::JumpListItem^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapJumpListItem(::Windows::UI::StartScreen::JumpListItem^ wintRtInstance);
    friend ::Windows::UI::StartScreen::JumpListItem^ UnwrapJumpListItem(Local<Value> value);
  };
  Persistent<FunctionTemplate> JumpListItem::s_constructorTemplate;

  v8::Local<v8::Value> WrapJumpListItem(::Windows::UI::StartScreen::JumpListItem^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(JumpListItem::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::StartScreen::JumpListItem^ UnwrapJumpListItem(Local<Value> value)
  {
     return JumpListItem::Unwrap<JumpListItem>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitJumpListItem(Local<Object> exports)
  {
    JumpListItem::Init(exports);
  }

  class JumpList : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("JumpList").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "saveAsync", SaveAsync);
      
                  
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("systemGroupKind").ToLocalChecked(), SystemGroupKindGetter, SystemGroupKindSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("items").ToLocalChecked(), ItemsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "isSupported", IsSupported);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(LoadCurrentAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("loadCurrentAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("JumpList").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    JumpList(::Windows::UI::StartScreen::JumpList^ instance)
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
      
      ::Windows::UI::StartScreen::JumpList^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpList^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::StartScreen::JumpList^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      JumpList *wrapperInstance = new JumpList(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpList^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::UI::StartScreen::JumpList^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::UI::StartScreen::JumpList^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapJumpList(winRtInstance));
    }


    static void SaveAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpList^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      JumpList *wrapper = JumpList::Unwrap<JumpList>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->SaveAsync();
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
  

    static void LoadCurrentAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::UI::StartScreen::JumpList^>^ op;
      

      if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::UI::StartScreen::JumpList::LoadCurrentAsync();
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

      opTask.then( [asyncToken] (task<::Windows::UI::StartScreen::JumpList^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapJumpList(result);
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

    static void IsSupported(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = ::Windows::UI::StartScreen::JumpList::IsSupported();
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

    static void SystemGroupKindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpList^>(info.This()))
      {
        return;
      }

      JumpList *wrapper = JumpList::Unwrap<JumpList>(info.This());

      try 
      {
        ::Windows::UI::StartScreen::JumpListSystemGroupKind result = wrapper->_instance->SystemGroupKind;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SystemGroupKindSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpList^>(info.This()))
      {
        return;
      }

      JumpList *wrapper = JumpList::Unwrap<JumpList>(info.This());

      try 
      {
        
        ::Windows::UI::StartScreen::JumpListSystemGroupKind winRtValue = static_cast<::Windows::UI::StartScreen::JumpListSystemGroupKind>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->SystemGroupKind = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ItemsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpList^>(info.This()))
      {
        return;
      }

      JumpList *wrapper = JumpList::Unwrap<JumpList>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVector<::Windows::UI::StartScreen::JumpListItem^>^ result = wrapper->_instance->Items;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Windows::UI::StartScreen::JumpListItem^>::CreateVectorWrapper(result, 
            [](::Windows::UI::StartScreen::JumpListItem^ val) -> Local<Value> {
              return WrapJumpListItem(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::JumpListItem^>(value);
            },
            [](Local<Value> value) -> ::Windows::UI::StartScreen::JumpListItem^ {
              return UnwrapJumpListItem(value);
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
    ::Windows::UI::StartScreen::JumpList^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapJumpList(::Windows::UI::StartScreen::JumpList^ wintRtInstance);
    friend ::Windows::UI::StartScreen::JumpList^ UnwrapJumpList(Local<Value> value);
  };
  Persistent<FunctionTemplate> JumpList::s_constructorTemplate;

  v8::Local<v8::Value> WrapJumpList(::Windows::UI::StartScreen::JumpList^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(JumpList::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::StartScreen::JumpList^ UnwrapJumpList(Local<Value> value)
  {
     return JumpList::Unwrap<JumpList>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitJumpList(Local<Object> exports)
  {
    JumpList::Init(exports);
  }

  class SecondaryTileVisualElements : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("SecondaryTileVisualElements").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("square150x150Logo").ToLocalChecked(), Square150x150LogoGetter, Square150x150LogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("showNameOnWide310x150Logo").ToLocalChecked(), ShowNameOnWide310x150LogoGetter, ShowNameOnWide310x150LogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("showNameOnSquare310x310Logo").ToLocalChecked(), ShowNameOnSquare310x310LogoGetter, ShowNameOnSquare310x310LogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("showNameOnSquare150x150Logo").ToLocalChecked(), ShowNameOnSquare150x150LogoGetter, ShowNameOnSquare150x150LogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("foregroundText").ToLocalChecked(), ForegroundTextGetter, ForegroundTextSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("backgroundColor").ToLocalChecked(), BackgroundColorGetter, BackgroundColorSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("wide310x150Logo").ToLocalChecked(), Wide310x150LogoGetter, Wide310x150LogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("square70x70Logo").ToLocalChecked(), Square70x70LogoGetter, Square70x70LogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("square310x310Logo").ToLocalChecked(), Square310x310LogoGetter, Square310x310LogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("square30x30Logo").ToLocalChecked(), Square30x30LogoGetter, Square30x30LogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("square71x71Logo").ToLocalChecked(), Square71x71LogoGetter, Square71x71LogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("square44x44Logo").ToLocalChecked(), Square44x44LogoGetter, Square44x44LogoSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("SecondaryTileVisualElements").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    SecondaryTileVisualElements(::Windows::UI::StartScreen::SecondaryTileVisualElements^ instance)
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
      
      ::Windows::UI::StartScreen::SecondaryTileVisualElements^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::StartScreen::SecondaryTileVisualElements^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      SecondaryTileVisualElements *wrapperInstance = new SecondaryTileVisualElements(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::UI::StartScreen::SecondaryTileVisualElements^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::UI::StartScreen::SecondaryTileVisualElements^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapSecondaryTileVisualElements(winRtInstance));
    }


  



    static void Square150x150LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->Square150x150Logo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Square150x150LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Square150x150Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ShowNameOnWide310x150LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        bool result = wrapper->_instance->ShowNameOnWide310x150Logo;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ShowNameOnWide310x150LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->ShowNameOnWide310x150Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ShowNameOnSquare310x310LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        bool result = wrapper->_instance->ShowNameOnSquare310x310Logo;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ShowNameOnSquare310x310LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->ShowNameOnSquare310x310Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ShowNameOnSquare150x150LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        bool result = wrapper->_instance->ShowNameOnSquare150x150Logo;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ShowNameOnSquare150x150LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->ShowNameOnSquare150x150Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ForegroundTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        ::Windows::UI::StartScreen::ForegroundText result = wrapper->_instance->ForegroundText;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ForegroundTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        ::Windows::UI::StartScreen::ForegroundText winRtValue = static_cast<::Windows::UI::StartScreen::ForegroundText>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ForegroundText = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void BackgroundColorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        ::Windows::UI::Color result = wrapper->_instance->BackgroundColor;
        info.GetReturnValue().Set(NodeRT::Utils::ColorToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BackgroundColorSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsColor(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        ::Windows::UI::Color winRtValue = NodeRT::Utils::ColorFromJs(value);

        wrapper->_instance->BackgroundColor = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void Wide310x150LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->Wide310x150Logo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Wide310x150LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Wide310x150Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void Square70x70LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->Square70x70Logo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Square70x70LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Square70x70Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void Square310x310LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->Square310x310Logo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Square310x310LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Square310x310Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void Square30x30LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->Square30x30Logo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Square30x30LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Square30x30Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void Square71x71LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->Square71x71Logo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Square71x71LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Square71x71Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void Square44x44LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->Square44x44Logo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void Square44x44LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(info.This()))
      {
        return;
      }

      SecondaryTileVisualElements *wrapper = SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Square44x44Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::UI::StartScreen::SecondaryTileVisualElements^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapSecondaryTileVisualElements(::Windows::UI::StartScreen::SecondaryTileVisualElements^ wintRtInstance);
    friend ::Windows::UI::StartScreen::SecondaryTileVisualElements^ UnwrapSecondaryTileVisualElements(Local<Value> value);
  };
  Persistent<FunctionTemplate> SecondaryTileVisualElements::s_constructorTemplate;

  v8::Local<v8::Value> WrapSecondaryTileVisualElements(::Windows::UI::StartScreen::SecondaryTileVisualElements^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SecondaryTileVisualElements::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::StartScreen::SecondaryTileVisualElements^ UnwrapSecondaryTileVisualElements(Local<Value> value)
  {
     return SecondaryTileVisualElements::Unwrap<SecondaryTileVisualElements>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSecondaryTileVisualElements(Local<Object> exports)
  {
    SecondaryTileVisualElements::Init(exports);
  }

  class SecondaryTile : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("SecondaryTile").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
      Local<Function> func;
      Local<FunctionTemplate> funcTemplate;
                  
      Nan::SetPrototypeMethod(localRef, "requestCreateAsync", RequestCreateAsync);
      Nan::SetPrototypeMethod(localRef, "requestCreateForSelectionAsync", RequestCreateForSelectionAsync);
      Nan::SetPrototypeMethod(localRef, "requestDeleteAsync", RequestDeleteAsync);
      Nan::SetPrototypeMethod(localRef, "requestDeleteForSelectionAsync", RequestDeleteForSelectionAsync);
      Nan::SetPrototypeMethod(localRef, "updateAsync", UpdateAsync);
      
            
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("shortName").ToLocalChecked(), ShortNameGetter, ShortNameSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("logo").ToLocalChecked(), LogoGetter, LogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("tileId").ToLocalChecked(), TileIdGetter, TileIdSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lockScreenDisplayBadgeAndTileText").ToLocalChecked(), LockScreenDisplayBadgeAndTileTextGetter, LockScreenDisplayBadgeAndTileTextSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lockScreenBadgeLogo").ToLocalChecked(), LockScreenBadgeLogoGetter, LockScreenBadgeLogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("arguments").ToLocalChecked(), ArgumentsGetter, ArgumentsSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("foregroundText").ToLocalChecked(), ForegroundTextGetter, ForegroundTextSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayName").ToLocalChecked(), DisplayNameGetter, DisplayNameSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("backgroundColor").ToLocalChecked(), BackgroundColorGetter, BackgroundColorSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("wideLogo").ToLocalChecked(), WideLogoGetter, WideLogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("tileOptions").ToLocalChecked(), TileOptionsGetter, TileOptionsSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("smallLogo").ToLocalChecked(), SmallLogoGetter, SmallLogoSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("roamingEnabled").ToLocalChecked(), RoamingEnabledGetter, RoamingEnabledSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("phoneticName").ToLocalChecked(), PhoneticNameGetter, PhoneticNameSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("visualElements").ToLocalChecked(), VisualElementsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);

      Nan::SetMethod(constructor, "exists", Exists);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FindAllAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("findAllAsync").ToLocalChecked(), func);
      func = Nan::GetFunction(Nan::New<FunctionTemplate>(FindAllForPackageAsync)).ToLocalChecked();
      Nan::Set(constructor, Nan::New<String>("findAllForPackageAsync").ToLocalChecked(), func);

      Nan::Set(exports, Nan::New<String>("SecondaryTile").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    SecondaryTile(::Windows::UI::StartScreen::SecondaryTile^ instance)
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
      
      ::Windows::UI::StartScreen::SecondaryTile^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::StartScreen::SecondaryTile^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 5
        && info[0]->IsString()
        && info[1]->IsString()
        && info[2]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[3])
        && info[4]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[2])));
          ::Windows::Foundation::Uri^ arg3 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[3]));
          ::Windows::UI::StartScreen::TileSize arg4 = static_cast<::Windows::UI::StartScreen::TileSize>(Nan::To<int32_t>(info[4]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::UI::StartScreen::SecondaryTile(arg0,arg1,arg2,arg3,arg4);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 6
        && info[0]->IsString()
        && info[1]->IsString()
        && info[2]->IsString()
        && info[3]->IsString()
        && info[4]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[5]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[2])));
          Platform::String^ arg3 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[3])));
          ::Windows::UI::StartScreen::TileOptions arg4 = static_cast<::Windows::UI::StartScreen::TileOptions>(Nan::To<int32_t>(info[4]).FromMaybe(0));
          ::Windows::Foundation::Uri^ arg5 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[5]));
          
          winRtInstance = ref new ::Windows::UI::StartScreen::SecondaryTile(arg0,arg1,arg2,arg3,arg4,arg5);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 7
        && info[0]->IsString()
        && info[1]->IsString()
        && info[2]->IsString()
        && info[3]->IsString()
        && info[4]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[5])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[6]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[2])));
          Platform::String^ arg3 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[3])));
          ::Windows::UI::StartScreen::TileOptions arg4 = static_cast<::Windows::UI::StartScreen::TileOptions>(Nan::To<int32_t>(info[4]).FromMaybe(0));
          ::Windows::Foundation::Uri^ arg5 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[5]));
          ::Windows::Foundation::Uri^ arg6 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[6]));
          
          winRtInstance = ref new ::Windows::UI::StartScreen::SecondaryTile(arg0,arg1,arg2,arg3,arg4,arg5,arg6);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          winRtInstance = ref new ::Windows::UI::StartScreen::SecondaryTile(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try
        {
          winRtInstance = ref new ::Windows::UI::StartScreen::SecondaryTile();
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

      SecondaryTile *wrapperInstance = new SecondaryTile(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::UI::StartScreen::SecondaryTile^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::UI::StartScreen::SecondaryTile^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapSecondaryTile(winRtInstance));
    }


    static void RequestCreateAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->RequestCreateAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsPoint(info[0]))
      {
        try
        {
          ::Windows::Foundation::Point arg0 = NodeRT::Utils::PointFromJs(info[0]);
          
          op = wrapper->_instance->RequestCreateAsync(arg0);
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
    static void RequestCreateForSelectionAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsRect(info[0]))
      {
        try
        {
          ::Windows::Foundation::Rect arg0 = NodeRT::Utils::RectFromJs(info[0]);
          
          op = wrapper->_instance->RequestCreateForSelectionAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsRect(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Rect arg0 = NodeRT::Utils::RectFromJs(info[0]);
          ::Windows::UI::Popups::Placement arg1 = static_cast<::Windows::UI::Popups::Placement>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->RequestCreateForSelectionAsync(arg0,arg1);
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
    static void RequestDeleteAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->RequestDeleteAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsPoint(info[0]))
      {
        try
        {
          ::Windows::Foundation::Point arg0 = NodeRT::Utils::PointFromJs(info[0]);
          
          op = wrapper->_instance->RequestDeleteAsync(arg0);
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
    static void RequestDeleteForSelectionAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 2
        && NodeRT::Utils::IsRect(info[0]))
      {
        try
        {
          ::Windows::Foundation::Rect arg0 = NodeRT::Utils::RectFromJs(info[0]);
          
          op = wrapper->_instance->RequestDeleteForSelectionAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsRect(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Rect arg0 = NodeRT::Utils::RectFromJs(info[0]);
          ::Windows::UI::Popups::Placement arg1 = static_cast<::Windows::UI::Popups::Placement>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->RequestDeleteForSelectionAsync(arg0,arg1);
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
    static void UpdateAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;
    

      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->UpdateAsync();
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
  

    static void FindAllAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::UI::StartScreen::SecondaryTile^>^>^ op;
      

      if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::UI::StartScreen::SecondaryTile::FindAllAsync();
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
          
          op = ::Windows::UI::StartScreen::SecondaryTile::FindAllAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::UI::StartScreen::SecondaryTile^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::UI::StartScreen::SecondaryTile^>::CreateVectorViewWrapper(result, 
            [](::Windows::UI::StartScreen::SecondaryTile^ val) -> Local<Value> {
              return WrapSecondaryTile(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(value);
            },
            [](Local<Value> value) -> ::Windows::UI::StartScreen::SecondaryTile^ {
              return UnwrapSecondaryTile(value);
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
    static void FindAllForPackageAsync(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction())
      {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
          return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::UI::StartScreen::SecondaryTile^>^>^ op;
      

      if (info.Length() == 1)
      {
        try
        {
          op = ::Windows::UI::StartScreen::SecondaryTile::FindAllForPackageAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::UI::StartScreen::SecondaryTile^>^> t) 
      {	
        try
        {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            
            Local<Value> error; 
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::UI::StartScreen::SecondaryTile^>::CreateVectorViewWrapper(result, 
            [](::Windows::UI::StartScreen::SecondaryTile^ val) -> Local<Value> {
              return WrapSecondaryTile(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(value);
            },
            [](Local<Value> value) -> ::Windows::UI::StartScreen::SecondaryTile^ {
              return UnwrapSecondaryTile(value);
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

    static void Exists(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          bool result;
          result = ::Windows::UI::StartScreen::SecondaryTile::Exists(arg0);
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

    static void ShortNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->ShortName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ShortNameSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->ShortName = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void LogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

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
    
    static void LogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Logo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void TileIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->TileId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TileIdSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->TileId = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void LockScreenDisplayBadgeAndTileTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        bool result = wrapper->_instance->LockScreenDisplayBadgeAndTileText;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LockScreenDisplayBadgeAndTileTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->LockScreenDisplayBadgeAndTileText = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void LockScreenBadgeLogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->LockScreenBadgeLogo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LockScreenBadgeLogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->LockScreenBadgeLogo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ArgumentsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Arguments;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ArgumentsSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Arguments = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ForegroundTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        ::Windows::UI::StartScreen::ForegroundText result = wrapper->_instance->ForegroundText;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ForegroundTextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        ::Windows::UI::StartScreen::ForegroundText winRtValue = static_cast<::Windows::UI::StartScreen::ForegroundText>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ForegroundText = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void DisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

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
    
    static void DisplayNameSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->DisplayName = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void BackgroundColorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        ::Windows::UI::Color result = wrapper->_instance->BackgroundColor;
        info.GetReturnValue().Set(NodeRT::Utils::ColorToJs(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BackgroundColorSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsColor(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        ::Windows::UI::Color winRtValue = NodeRT::Utils::ColorFromJs(value);

        wrapper->_instance->BackgroundColor = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void WideLogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->WideLogo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void WideLogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->WideLogo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void TileOptionsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        ::Windows::UI::StartScreen::TileOptions result = wrapper->_instance->TileOptions;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TileOptionsSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        ::Windows::UI::StartScreen::TileOptions winRtValue = static_cast<::Windows::UI::StartScreen::TileOptions>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->TileOptions = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void SmallLogoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        ::Windows::Foundation::Uri^ result = wrapper->_instance->SmallLogo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Uri", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SmallLogoSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        ::Windows::Foundation::Uri^ winRtValue = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->SmallLogo = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void RoamingEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        bool result = wrapper->_instance->RoamingEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RoamingEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->RoamingEnabled = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void PhoneticNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->PhoneticName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void PhoneticNameSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->PhoneticName = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void VisualElementsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
      {
        return;
      }

      SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());

      try 
      {
        ::Windows::UI::StartScreen::SecondaryTileVisualElements^ result = wrapper->_instance->VisualElements;
        info.GetReturnValue().Set(WrapSecondaryTileVisualElements(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
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
      if (NodeRT::Utils::CaseInsenstiveEquals(L"visualElementsRequested", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());
      
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

          registrationToken = wrapper->_instance->VisualElementsRequested::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::StartScreen::SecondaryTile^, ::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^>(
            [callbackObjPtr](::Windows::UI::StartScreen::SecondaryTile^ arg0, ::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapSecondaryTile(arg0);
                  wrappedArg1 = WrapVisualElementsRequestedEventArgs(arg1);


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

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"visualElementsRequested", str)))
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
        if (NodeRT::Utils::CaseInsenstiveEquals(L"visualElementsRequested", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTile^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          SecondaryTile *wrapper = SecondaryTile::Unwrap<SecondaryTile>(info.This());
          wrapper->_instance->VisualElementsRequested::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::UI::StartScreen::SecondaryTile^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapSecondaryTile(::Windows::UI::StartScreen::SecondaryTile^ wintRtInstance);
    friend ::Windows::UI::StartScreen::SecondaryTile^ UnwrapSecondaryTile(Local<Value> value);
  };
  Persistent<FunctionTemplate> SecondaryTile::s_constructorTemplate;

  v8::Local<v8::Value> WrapSecondaryTile(::Windows::UI::StartScreen::SecondaryTile^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SecondaryTile::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::StartScreen::SecondaryTile^ UnwrapSecondaryTile(Local<Value> value)
  {
     return SecondaryTile::Unwrap<SecondaryTile>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSecondaryTile(Local<Object> exports)
  {
    SecondaryTile::Init(exports);
  }

  class VisualElementsRequestedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("VisualElementsRequestedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("request").ToLocalChecked(), RequestGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("VisualElementsRequestedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    VisualElementsRequestedEventArgs(::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^ instance)
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
      
      ::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      VisualElementsRequestedEventArgs *wrapperInstance = new VisualElementsRequestedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapVisualElementsRequestedEventArgs(winRtInstance));
    }


  



    static void RequestGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^>(info.This()))
      {
        return;
      }

      VisualElementsRequestedEventArgs *wrapper = VisualElementsRequestedEventArgs::Unwrap<VisualElementsRequestedEventArgs>(info.This());

      try 
      {
        ::Windows::UI::StartScreen::VisualElementsRequest^ result = wrapper->_instance->Request;
        info.GetReturnValue().Set(WrapVisualElementsRequest(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapVisualElementsRequestedEventArgs(::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^ wintRtInstance);
    friend ::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^ UnwrapVisualElementsRequestedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> VisualElementsRequestedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapVisualElementsRequestedEventArgs(::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(VisualElementsRequestedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::StartScreen::VisualElementsRequestedEventArgs^ UnwrapVisualElementsRequestedEventArgs(Local<Value> value)
  {
     return VisualElementsRequestedEventArgs::Unwrap<VisualElementsRequestedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitVisualElementsRequestedEventArgs(Local<Object> exports)
  {
    VisualElementsRequestedEventArgs::Init(exports);
  }

  class VisualElementsRequest : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("VisualElementsRequest").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("alternateVisualElements").ToLocalChecked(), AlternateVisualElementsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deadline").ToLocalChecked(), DeadlineGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("visualElements").ToLocalChecked(), VisualElementsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("VisualElementsRequest").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    VisualElementsRequest(::Windows::UI::StartScreen::VisualElementsRequest^ instance)
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
      
      ::Windows::UI::StartScreen::VisualElementsRequest^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequest^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::StartScreen::VisualElementsRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      VisualElementsRequest *wrapperInstance = new VisualElementsRequest(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequest^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::UI::StartScreen::VisualElementsRequest^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::UI::StartScreen::VisualElementsRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapVisualElementsRequest(winRtInstance));
    }


  
    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequest^>(info.This()))
      {
        return;
      }

      VisualElementsRequest *wrapper = VisualElementsRequest::Unwrap<VisualElementsRequest>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::UI::StartScreen::VisualElementsRequestDeferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(WrapVisualElementsRequestDeferral(result));
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



    static void AlternateVisualElementsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequest^>(info.This()))
      {
        return;
      }

      VisualElementsRequest *wrapper = VisualElementsRequest::Unwrap<VisualElementsRequest>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::UI::StartScreen::SecondaryTileVisualElements^>^ result = wrapper->_instance->AlternateVisualElements;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::UI::StartScreen::SecondaryTileVisualElements^>::CreateVectorViewWrapper(result, 
            [](::Windows::UI::StartScreen::SecondaryTileVisualElements^ val) -> Local<Value> {
              return WrapSecondaryTileVisualElements(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::SecondaryTileVisualElements^>(value);
            },
            [](Local<Value> value) -> ::Windows::UI::StartScreen::SecondaryTileVisualElements^ {
              return UnwrapSecondaryTileVisualElements(value);
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
    
    static void DeadlineGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequest^>(info.This()))
      {
        return;
      }

      VisualElementsRequest *wrapper = VisualElementsRequest::Unwrap<VisualElementsRequest>(info.This());

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
    
    static void VisualElementsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequest^>(info.This()))
      {
        return;
      }

      VisualElementsRequest *wrapper = VisualElementsRequest::Unwrap<VisualElementsRequest>(info.This());

      try 
      {
        ::Windows::UI::StartScreen::SecondaryTileVisualElements^ result = wrapper->_instance->VisualElements;
        info.GetReturnValue().Set(WrapSecondaryTileVisualElements(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::StartScreen::VisualElementsRequest^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapVisualElementsRequest(::Windows::UI::StartScreen::VisualElementsRequest^ wintRtInstance);
    friend ::Windows::UI::StartScreen::VisualElementsRequest^ UnwrapVisualElementsRequest(Local<Value> value);
  };
  Persistent<FunctionTemplate> VisualElementsRequest::s_constructorTemplate;

  v8::Local<v8::Value> WrapVisualElementsRequest(::Windows::UI::StartScreen::VisualElementsRequest^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(VisualElementsRequest::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::StartScreen::VisualElementsRequest^ UnwrapVisualElementsRequest(Local<Value> value)
  {
     return VisualElementsRequest::Unwrap<VisualElementsRequest>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitVisualElementsRequest(Local<Object> exports)
  {
    VisualElementsRequest::Init(exports);
  }

  class VisualElementsRequestDeferral : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("VisualElementsRequestDeferral").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "complete", Complete);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
	  Nan::SetMethod(constructor, "castFrom", CastFrom);


      Nan::Set(exports, Nan::New<String>("VisualElementsRequestDeferral").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    VisualElementsRequestDeferral(::Windows::UI::StartScreen::VisualElementsRequestDeferral^ instance)
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
      
      ::Windows::UI::StartScreen::VisualElementsRequestDeferral^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequestDeferral^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::StartScreen::VisualElementsRequestDeferral^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      VisualElementsRequestDeferral *wrapperInstance = new VisualElementsRequestDeferral(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


	
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info)
    {
		HandleScope scope;
		if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequestDeferral^>(info[0]))
		{
			Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
			return;
		}

		::Windows::UI::StartScreen::VisualElementsRequestDeferral^ winRtInstance;
		try
		{
			winRtInstance = (::Windows::UI::StartScreen::VisualElementsRequestDeferral^) NodeRT::Utils::GetObjectInstance(info[0]);
		}
		catch (Platform::Exception ^exception)
		{
			NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
			return;
		}

		info.GetReturnValue().Set(WrapVisualElementsRequestDeferral(winRtInstance));
    }


  
    static void Complete(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::StartScreen::VisualElementsRequestDeferral^>(info.This()))
      {
        return;
      }

      VisualElementsRequestDeferral *wrapper = VisualElementsRequestDeferral::Unwrap<VisualElementsRequestDeferral>(info.This());

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
    ::Windows::UI::StartScreen::VisualElementsRequestDeferral^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapVisualElementsRequestDeferral(::Windows::UI::StartScreen::VisualElementsRequestDeferral^ wintRtInstance);
    friend ::Windows::UI::StartScreen::VisualElementsRequestDeferral^ UnwrapVisualElementsRequestDeferral(Local<Value> value);
  };
  Persistent<FunctionTemplate> VisualElementsRequestDeferral::s_constructorTemplate;

  v8::Local<v8::Value> WrapVisualElementsRequestDeferral(::Windows::UI::StartScreen::VisualElementsRequestDeferral^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(VisualElementsRequestDeferral::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::StartScreen::VisualElementsRequestDeferral^ UnwrapVisualElementsRequestDeferral(Local<Value> value)
  {
     return VisualElementsRequestDeferral::Unwrap<VisualElementsRequestDeferral>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitVisualElementsRequestDeferral(Local<Object> exports)
  {
    VisualElementsRequestDeferral::Init(exports);
  }

} } } } 

NAN_MODULE_INIT(init)
{
  // we ignore failures for now since it probably means that the initialization already happened for STA, and that's cool
  CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  //if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
  /*{
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }*/
  
  NodeRT::Windows::UI::StartScreen::InitJumpListSystemGroupKindEnum(target);
  NodeRT::Windows::UI::StartScreen::InitJumpListItemKindEnum(target);
  NodeRT::Windows::UI::StartScreen::InitTileOptionsEnum(target);
  NodeRT::Windows::UI::StartScreen::InitTileSizeEnum(target);
  NodeRT::Windows::UI::StartScreen::InitForegroundTextEnum(target);
  NodeRT::Windows::UI::StartScreen::InitJumpListItem(target);
  NodeRT::Windows::UI::StartScreen::InitJumpList(target);
  NodeRT::Windows::UI::StartScreen::InitSecondaryTileVisualElements(target);
  NodeRT::Windows::UI::StartScreen::InitSecondaryTile(target);
  NodeRT::Windows::UI::StartScreen::InitVisualElementsRequestedEventArgs(target);
  NodeRT::Windows::UI::StartScreen::InitVisualElementsRequest(target);
  NodeRT::Windows::UI::StartScreen::InitVisualElementsRequestDeferral(target);

  NodeRT::Utils::RegisterNameSpace("Windows.UI.StartScreen", target);
}


NODE_MODULE(binding, init)