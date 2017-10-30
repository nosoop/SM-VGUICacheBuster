# VGUI Cache Buster

A workaround for webviews not updating when loading pages on the same domain.

This plugin attempts to fix an issue with the Steam webview that prevents it from changing pages
in certain cases.  It is a drop-in and configurable solution that hooks and modifies the user
messages that display web content.

## Workarounds

### The "proxy" method

The "proxy" method uses a static page that takes a URL embedded as a location hash and renders
it in an `<iframe>` element.

It works perfectly when it can, though a non-trivial number of pages do not permit cross-origin
framing (Google, YouTube, Steam group pages, among others).

This method requires a static page to be served over HTTP(S).  The default provided is
(currently) a valid copy, though it does mean you're putting trust on a page outside of your
own control.

### The "delayed load" method

The second method forces the client to navigate away from the page, waiting a short amount of
time, and transmitting the requested page later.  The first request is made to 0.0.0.0 (an
invalid IP address), which should fail immediately.

From my testing, this workaround works most of the time, and no `<iframe>` element is required.
However, it does induce a delay.

## Configuration

### ConVars

There are a couple of configuration settings:

* `vgui_workaround_proxy_page`:  Configures the URL to the page used in the "proxy" method.
If you have web hosting, take the file at `www/motd_proxy.html`, make it available online, and
set this ConVar to the URL of that page.
* `vgui_workaround_delay_time`:  Configures the delay between navigating to an invalid page and
to the requested page.  Value is in seconds.

### URL configuration

A configuration file is provided as `configs/vgui_cache_buster_urls.cfg`.  In the file, you
can add a number of URL prefixes (without the protocol specifier), to be handled by either
workaround or to bypass the workaround.  See the provided file for more details.
