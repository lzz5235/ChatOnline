TOPDIR = ..

SUBDIRS =

-include $(TOPDIR)/makefiles/gmake/sub.mk

doc:
	cd $(TOPDIR); doxygen docs/doxygen.conf

local_clean:
	-@rm -rf doxygen 2>/dev/null

local_install:
	$(INSTALL) -d -m 755 $(datadir)/doc/sqlite3xx
	$(INSTALL) -m 644 doxygen/html/* $(datadir)/doc/sqlite3xx
#	$(INSTALL) -d -m 755 $(datadir)/man/man3
#	$(INSTALL) -m 644 doxygen/man/man3/* $(datadir)/man/man3

local_uninstall:
	@-rm -rf $(datadir)/doc/sqlite3xx
