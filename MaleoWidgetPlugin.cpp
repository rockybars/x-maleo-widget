#include "MaleoWidgetPlugin.h"

#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>

const std::string MaleoWidgetPlugin::s_strPluginName("maleo-npapi");
const std::string MaleoWidgetPlugin::s_strPluginDescription(" (Maleo simple plugin)");
const std::string MaleoWidgetPlugin::s_strPluginVersion("1.0.0.0");
	
NPNetscapeFuncs* MaleoWidgetPlugin::s_pBrowserFunctions = NULL;

void MaleoWidgetPlugin::setBrowserFunctions(NPNetscapeFuncs* const pBrowserFunctions)
{
  s_pBrowserFunctions = pBrowserFunctions;
}

const std::string& MaleoWidgetPlugin::getPluginName()
{
  return s_strPluginName;
}

const std::string& MaleoWidgetPlugin::getPluginDescription()
{
  return s_strPluginDescription;
}

const std::string& MaleoWidgetPlugin::getPluginVersion()
{
  return s_strPluginVersion;
}

MaleoWidgetPlugin::MaleoWidgetPlugin(const NPP instance, const NPMIMEType mimeType, const uint16_t mode, const std::map<std::string, std::string> mapArgs, const NPSavedData * const saved)
  :  m_bHasSize(mapArgs.count("width") && mapArgs.count("height")),
     m_bEmbedded(mode == NP_EMBED),
     m_mapArgs(mapArgs),
     m_npp(instance)
{
  if (s_pBrowserFunctions == NULL)
    throw std::runtime_error("s_pBrowserFunctions not set!");
}

MaleoWidgetPlugin::~MaleoWidgetPlugin()
{
  // FIXME: cleanup!
}

NPError MaleoWidgetPlugin::setWindow(const NPWindow * const window)
{
   // FIXME: check if it is already created; make it singleton?
   // this is only a simple example
   m_window = gtk_plug_new(reinterpret_cast<Window>(window->window));
   gtk_widget_realize(m_window);
   GtkWidget * button = gtk_button_new_with_label("Hello, this is a GtkWidget!");
   GtkWidget * vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
   gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);
   gtk_widget_show(button);

   gtk_container_add(GTK_CONTAINER(m_window), vbox);
   gtk_widget_show(vbox);
   gtk_widget_set_size_request(m_window, window->width, window->height);
   gtk_widget_show(m_window);      

   return NPERR_NO_ERROR;
}

NPError MaleoWidgetPlugin::newStream(const NPMIMEType mimeType, const NPStream * const stream, const NPBool seekable, uint16_t * const stype)
{
  return NPERR_NO_ERROR;
}

NPError MaleoWidgetPlugin::destroyStream(const NPStream * const stream, const NPReason reason)
{
  return NPERR_NO_ERROR;
}

int32_t MaleoWidgetPlugin::writeReady(const NPStream * const stream)
{
  return 0;
}

int32_t MaleoWidgetPlugin::write(const NPStream * const stream, const int32_t offset, const int32_t len, const void * const buffer)
{	
  return 0;
}

int16_t MaleoWidgetPlugin::handleEvent(const void * const pEvent)
{
  return 0;
}

void MaleoWidgetPlugin::streamAsFile(const NPStream * const stream, const std::string strName) const
{
}

void MaleoWidgetPlugin::print(const NPPrint * const platformPrint) const
{
}

void MaleoWidgetPlugin::URLNotify(const std::string strURL, const NPReason reason, const void * const notifyData) const
{
}

NPError MaleoWidgetPlugin::getValue(const NPPVariable variable, const void * const value) const
{
  return NPERR_GENERIC_ERROR;
}

NPError MaleoWidgetPlugin::setValue(const NPNVariable variable, const void * const value) const
{
  return NPERR_GENERIC_ERROR;
}
