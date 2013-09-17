TOPDIR = ..

-include $(TOPDIR)/makefiles/gmake/sub.mk

local_all:

local_clean:
	-@rm -f sqlite3xx/*.bak
	-@rm -f sqlite3xx/*~

local_install:
	$(INSTALL) -d -m 755 $(includedir)/sqlite3xx
	$(INSTALL) -m 644 sqlite3xx/*.hpp $(includedir)/sqlite3xx
	$(INSTALL) -m 644 sqlite3xx/sqlite3xx $(includedir)/sqlite3xx
	$(INSTALL) -d -m 755 $(includedir)/sqlite3xx/port
	$(INSTALL) -m 644 sqlite3xx/port/*.hpp $(includedir)/sqlite3xx/port
	$(INSTALL) -m 644 sqlite3xx/port/*.h $(includedir)/sqlite3xx/port

local_uninstall:
	-@rm -rf $(includedir)/sqlite3xx
