# VGUI Cache Buster

A workaround for webviews not updating when loading pages on the same domain in Source Engine
games.

This plugin attempts to fix an issue with the Steam webview that prevents it from changing pages
in certain cases.  It is a drop-in and configurable solution that hooks and modifies the user
messages that display web content.

Tested to work in Team Fortress 2.  Proxy method also tested in Empires.  Should work in most
other games that support web panels.

The plugin also handles CS:GO-specific quirks in opening web pages.  Using `ShowMOTDPanel` in
SourcePawn will now make the page visible to the user, rather than showing an empty gray panel.

## Workarounds

Here are details of the workarounds used to force in-game webviews to update.

### The "proxy" method

The "proxy" method uses a static page that takes a URL embedded as a location hash and renders
it in an `<iframe>` element.  This method works because location hash changes are still
propagated.

It works almost seamlessly when this method is usable, though a not insignificant number of
pages do not permit cross-origin framing (Google, YouTube, Steam group pages, among others).

This method requires a static page to be served over HTTP(S).  The default provided is
(currently) a valid copy, though it does mean you're putting trust on a page outside of your
own control.  You can host a copy yourself; see the configuration section below.

### The "delayed load" method

The second method forces the client to first navigate away from the page, waiting a short amount
of time, and then transmitting the requested page later.  The first request is made to 0.0.0.0
(an invalid IP address), which should fail immediately.

From my testing, this workaround works most of the time, and no `<iframe>` element is required.
However, it does induce a delay, and it seems to fail occasionally.

## Extensions

Extensions have been added where custom keys/values introduce new behavior that are handled with
the plugin.

* `x-vgui-width` and `x-vgui-height` communicate the popup size in CS:GO.

See `include/vgui_motd_stocks.inc` to see how.

## Configuration

### ConVars

There are a couple of configuration settings available in
`cfg/sourcemod/plugin.vgui_cache_buster.cfg`:

* `vgui_workaround_proxy_page`:  Configures the URL to the page used in the "proxy" method.
If you have web hosting, you can take the file at `www/motd_proxy.html`, make it available
online, and set this ConVar to the URL of that page.
* `vgui_workaround_delay_time`:  Configures the delay between navigating to an invalid page and
to the requested page.  Value is in seconds.

### URL configuration

A configuration file is provided as `configs/vgui_cache_buster_urls.cfg`.  In the file, you
can add a number of URL prefixes (without the protocol specifier), to be handled by either
workaround or to bypass the workaround.

See the provided file for more details.

### CS:GO-specific configuration

CS:GO should only use the "delayed load" method.  There is an additional workaround implemented
specifically for CS:GO that opens visible pages as a pop-up window, which is handled by a
different proxy page that calls `window.open)`.

1.  Set your `vgui_workaround_proxy_page` ConVar to a hosted copy of `www/popup_proxy.html`.
You can also set the value to `http://motdproxy.us.to/popup.html`.
2.  Rename `configs/vgui_cache_buster_urls_csgo.cfg` to `configs/vgui_cache_buster_urls.cfg`.
This forces usage of the wildcard and makes all URLs use the delayed load method.
	* You theoretically *can* set pages that will always be displayed to use the `proxy` method
	instead (as visible popups will just keep using the proxy).  Any hidden pages will still
	need to use the delayed load, however.
3.	Reload the plugin.
