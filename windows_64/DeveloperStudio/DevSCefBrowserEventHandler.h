/*
* Copyright (c) 2015, WSO2 Inc. (http://www.wso2.org) All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_

#include "include/cef_client.h"

#include <list>


#define ClientWindowHandle CefWindowHandle


class DevSCefBrowserEventHandler : public CefClient,
	public CefDisplayHandler,
	public CefDownloadHandler,
	public CefLifeSpanHandler,
	public CefLoadHandler {
public:
	DevSCefBrowserEventHandler();
	~DevSCefBrowserEventHandler();

	// Provide access to the single global instance of this object.
	static DevSCefBrowserEventHandler* GetInstance();

	// CefClient methods:
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE {
		return this;
	}
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
		return this;
	}
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {
		return this;
	}

	virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler() OVERRIDE {
		return this;
	}

	// CefDisplayHandler methods:
	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
		const CefString& title) OVERRIDE;

	// CefLifeSpanHandler methods:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

	// CefLoadHandler methods:
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl) OVERRIDE;

	// CefDownloadHandler methods
	virtual void OnBeforeDownload(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		const CefString& suggested_name,
		CefRefPtr<CefBeforeDownloadCallback> callback) OVERRIDE;

	virtual void OnDownloadUpdated(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		CefRefPtr<CefDownloadItemCallback> callback) OVERRIDE;

	void SetLastDownloadFile(const std::string& fileName);
	std::string GetLastDownloadFile() const;

	// Send a notification to the application. Notifications should not block the
	// caller.
	enum NotificationType {
		NOTIFY_CONSOLE_MESSAGE,
		NOTIFY_DOWNLOAD_COMPLETE,
		NOTIFY_DOWNLOAD_ERROR,
	};

	void SendNotification(NotificationType type);
	void SetMainWindowHandle(ClientWindowHandle handle);
	ClientWindowHandle GetMainWindowHandle() const;

	// Request that all existing browser windows close.
	void CloseAllBrowsers(bool force_close);

	bool IsClosing() const { return is_closing_; }

private:
	// List of existing browser windows. Only accessed on the CEF UI thread.
	typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
	BrowserList browser_list_;

	bool is_closing_;

	// Returns the full download path for the specified file, or an empty path to
	// use the default temp directory.
	std::string GetDownloadPath(const std::string& file_name);

	// Support for downloading files.
	std::string last_download_file_;

	// The main frame window handle.
	ClientWindowHandle main_handle_;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(DevSCefBrowserEventHandler);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
