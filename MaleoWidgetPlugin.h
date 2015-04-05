#ifndef MALEO_WIDGET_PLUGIN_H
#define MALEO_WIDGET_PLUGIN_H

#include "npapi.h"
#include "npfunctions.h"

#include <map>
#include <string>
#include <gtk/gtk.h>

class MaleoWidgetPlugin
{
public: 
  MaleoWidgetPlugin( const NPP instance, const NPMIMEType mimeType, const uint16_t mode, const std::map<std::string, std::string> mapArgs, const NPSavedData * const saved );
  ~MaleoWidgetPlugin();
  
  static void setBrowserFunctions( NPNetscapeFuncs * const pBrowserFunctions );
  static const std::string & getPluginName();
  static const std::string & getPluginDescription();
  static const std::string & getPluginVersion();

  NPError setWindow(const NPWindow * const window);
  NPError newStream(const NPMIMEType mimeType, const NPStream * const stream, const NPBool seekable, uint16_t * const stype);
  NPError destroyStream(const NPStream * const stream, const NPReason reason);

  int32_t writeReady(const NPStream * const stream);
  int32_t write(const NPStream * const stream, const int32_t offset, const int32_t len, const void * const buffer);

  int16_t handleEvent(const void * const event);

  void streamAsFile(const NPStream * const stream, const std::string strName) const;
  void print(const NPPrint * const platformPrint) const;
  void URLNotify(const std::string strURL, const NPReason reason, const void * const notifyData) const;
  NPError getValue(const NPPVariable variable, const void * const value) const;
  NPError setValue(const NPNVariable variable, const void * const value) const;
	
private:
  static NPNetscapeFuncs * s_pBrowserFunctions;

  /* Plugin properties */
  static const std::string s_strPluginName;
  static const std::string s_strPluginDescription;
  static const std::string s_strPluginVersion;
		
  const bool m_bHasSize;
  const bool m_bEmbedded;
  std::map<std::string, std::string> m_mapArgs;
	
  NPP m_npp;
  GtkWidget * m_window;
};

#endif
