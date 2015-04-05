#include "maleo-npapi.h"

#include <map>
#include <stdexcept>

#include "MaleoWidgetPlugin.h"

static char * const szVersion = "1.0.0"; 

// Called when plugin is loaded by browser
NP_EXPORT(NPError) NP_Initialize(NPNetscapeFuncs * bFuncs, NPPluginFuncs * pFuncs)
{
  MaleoWidgetPlugin::setBrowserFunctions(bFuncs);

  if( pFuncs->size < ( offsetof(NPPluginFuncs, setvalue) + sizeof(void*) ) )
    return NPERR_INVALID_FUNCTABLE_ERROR;

  pFuncs->newp = NPP_New;
  pFuncs->destroy = NPP_Destroy;
  pFuncs->setwindow = NPP_SetWindow;
  pFuncs->newstream = NPP_NewStream;
  pFuncs->destroystream = NPP_DestroyStream;
  pFuncs->asfile = NPP_StreamAsFile;
  pFuncs->writeready = NPP_WriteReady;
  pFuncs->write = NPP_Write;
  pFuncs->print = NPP_Print;
  pFuncs->event = NPP_HandleEvent;
  pFuncs->urlnotify = NPP_URLNotify;
  pFuncs->getvalue = NPP_GetValue;
  pFuncs->setvalue = NPP_SetValue;
  
  return NPERR_NO_ERROR;
}

NP_EXPORT(char*) NP_GetPluginVersion()
{
  return szVersion;
}

NP_EXPORT(const char*) NP_GetMIMEDescription()
{
  // FIXME: should be put somewhere else
  return (char*) "application/x-maleo-widget:maleo:Maleo widget";
}

NP_EXPORT(NPError) NP_GetValue(void* future, NPPVariable aVariable, void* aValue)
{
  switch (aVariable)
  {
    case NPPVpluginNameString:
      *((const char **) aValue) = MaleoWidgetPlugin::getPluginName().c_str();
    break;
     
    case NPPVpluginDescriptionString:
      *((const char**)aValue) = MaleoWidgetPlugin::getPluginDescription().c_str();
    break;

    case NPPVpluginNeedsXEmbed:
      *((bool *)aValue) = true;
    break;

    default:
      return NPERR_INVALID_PARAM;
    break;
  }
  return NPERR_NO_ERROR;
}

NP_EXPORT(NPError) NP_Shutdown()
{
  return NPERR_NO_ERROR;
}

// Called for each new instance of the plugin
NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char* argn[], char* argv[], NPSavedData* saved)
{
  try
  {
    // Add try/catch for memory-allocation error
    std::map<std::string, std::string> mapArgs;
    for (int16_t i = 0; i < argc; ++i)
      mapArgs[ argn[i] ] = argv[i];

    // Create plugin instance and save in instance-data		
    MaleoWidgetPlugin * pPlugin = new MaleoWidgetPlugin( instance, pluginType, mode, mapArgs, saved );
    instance->pdata = pPlugin;
  } 
  catch (std::runtime_error & exception)
  {
    return NPERR_GENERIC_ERROR;
  }
  return NPERR_NO_ERROR;
}

NPError NPP_Destroy(NPP instance, NPSavedData * * save)
{
  MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  delete pPlugin;
  return NPERR_NO_ERROR;
}

NPError NPP_SetWindow(NPP instance, NPWindow * window)
{
  MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  return pPlugin->setWindow(window);
}

NPError NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16_t* stype)
{
  MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  return pPlugin->newStream(type, stream, seekable, stype);
}

NPError NPP_DestroyStream(NPP instance, NPStream* stream, NPReason reason)
{
  MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  return pPlugin->destroyStream(stream, reason);
}

int32_t NPP_WriteReady(NPP instance, NPStream* stream)
{
  MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  return pPlugin->writeReady(stream);
}

int32_t NPP_Write(NPP instance, NPStream* stream, int32_t offset, int32_t len, void* buffer)
{
  MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  return pPlugin->write(stream, offset, len, buffer);
}

void NPP_StreamAsFile(NPP instance, NPStream* stream, const char* fname)
{
  MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  return pPlugin->streamAsFile(stream, fname);
}

void NPP_Print(NPP instance, NPPrint* platformPrint)
{
  MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  return pPlugin->print(platformPrint);
}

int16_t NPP_HandleEvent(NPP instance, void* event)
{
  MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  return pPlugin->handleEvent(event);
}

void NPP_URLNotify(NPP instance, const char* URL, NPReason reason, void* notifyData)
{
  MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  return pPlugin->URLNotify(URL, reason, notifyData);
}

NPError NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
  return NP_GetValue(NULL, variable, value);
  // FIXME: put in plugin?
  //MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  //return pPlugin->getValuevariable, value);
}

NPError NPP_SetValue(NPP instance, NPNVariable variable, void *value)
{
  MaleoWidgetPlugin * pPlugin = static_cast<MaleoWidgetPlugin *>(instance->pdata);
  return pPlugin->setValue(variable, value);
}

