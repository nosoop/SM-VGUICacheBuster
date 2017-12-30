all: build/package.zip

# the things you have to do for gnuwin32
build/package.zip: plugins/vgui_cache_buster.smx
	"mkdir" -p build
	zip build/package.zip configs/* scripting/*.sp scripting/*/*.sp www/* plugins/* scripting/include/*

plugins/vgui_cache_buster.smx: scripting/vgui_cache_buster.sp
	"mkdir" -p plugins
	spcomp scripting/vgui_cache_buster.sp -o plugins/vgui_cache_buster.smx -i scripting/

clean:
	rm -fr build/ plugins/
