all: build/output.zip

# the things you have to do for gnuwin32
build/output.zip: plugins/vgui_cache_buster.smx
	"mkdir" -p build
	zip build/package.zip configs/* scripting/*.sp www/* plugins/*

plugins/vgui_cache_buster.smx:
	"mkdir" -p plugins
	spcomp scripting/vgui_cache_buster.sp -o plugins/vgui_cache_buster.smx

clean:
	rm -fr build/ plugins/
