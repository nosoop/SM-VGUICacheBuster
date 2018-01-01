# VGUI URL Cache Buster

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

The "proxy" method uses a static page that takes parameters as a location hash and handles it
through one of two methods:

* Renders it in an `<iframe>` element.  Works seamlessly&hellip; as long as your page supports
cross-origin framing (popular sites including Google, YouTube, and Steam don't).
* Opens the URL into a new window.  Used for CS:GO and when plugins explicitly request popup
windows (see the extensions section).

As location hashes are propagated regardless of being in the same domain, pages are displayed
immediately.

This method requires a static page to be served over HTTP(S).  The default provided is
(currently) a valid copy, though it does mean you're putting trust on a page outside of your
own control.

You can host a copy yourself; see the configuration section below.

### The "delayed load" method

This method forces the client to first navigate away from the page, waiting a short amount of
time, and then transmitting the requested page later.  The first request is made to 0.0.0.0
(an invalid IP address), which should fail immediately.

From my testing, this workaround works most of the time, and no `<iframe>` element is required,
meaning it should work with every site.  However, it does induce a delay, and it may fail
occasionally.

## Extensions

Extensions have been added where custom keys/values in the usermessage introduce new behavior
that are handled through this plugin.

* `x-vgui-popup` determines if the message should be displayed in a popup window.
* `x-vgui-width` and `x-vgui-height` determine the popup size.  If it is set to 0 or is not
defined, it will use the screen dimensions as determined by the embedded browser.

See `include/vgui_motd_stocks.inc` to see how they work.

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
workaround or to bypass the workaround entirely.

See the provided file for more details.

### CS:GO-specific configuration

Any `ShowMOTDPanel` calls that are supposed to make visible panels in CS:GO are rewritten to use
a popup by default.

No additional configuration is necessary.
