# VGUI Cache Buster

A workaround for webviews not updating when loading pages on the same domain in Source Engine
games.

This plugin attempts to fix an issue with the Steam webview that prevents it from changing pages
in certain cases.  It is a drop-in and configurable solution that hooks and modifies the user
messages that display web content.

Tested to work in Team Fortress 2.  Proxy method also tested in Empires.
Probably won't work in CS:GO (as they use protobufs instead of bitbuffers for usermessages).

## Workarounds

Here are details of the workarounds used to force in-game webviews to update.

### The "proxy" method

The "proxy" method uses a static page that takes a URL embedded as a location hash and renders
it in an `<iframe>` element.

It works perfectly when it can, though a non-trivial number of pages do not permit cross-origin
framing (Google, YouTube, Steam group pages, among others).

This method requires a static page to be served over HTTP(S).  The default provided is
(currently) a valid copy, though it does mean you're putting trust on a page outside of your
own control.

### The "delayed load" method

The second method forces the client to first navigate away from the page, waiting a short amount
of time, and then transmitting the requested page later.  The first request is made to 0.0.0.0
(an invalid IP address), which should fail immediately.

From my testing, this workaround works most of the time, and no `<iframe>` element is required.
However, it does induce a delay, and it seems to fail occasionally.

## Configuration

### ConVars

There are a couple of configuration settings available in
`cfg/sourcemod/plugin.vgui_cache_buster.cfg`:

* `vgui_workaround_proxy_page`:  Configures the URL to the page used in the "proxy" method.
If you have web hosting, take the file at `www/motd_proxy.html`, make it available online, and
set this ConVar to the URL of that page.
* `vgui_workaround_delay_time`:  Configures the delay between navigating to an invalid page and
to the requested page.  Value is in seconds.

### URL configuration

A configuration file is provided as `configs/vgui_cache_buster_urls.cfg`.  In the file, you
can add a number of URL prefixes (without the protocol specifier), to be handled by either
workaround or to bypass the workaround.

See the provided file for more details.