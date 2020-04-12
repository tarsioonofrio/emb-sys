export CHEDDAR_INSTALL_PATH=usr/src/cheddar/
export PATH=$GNAT_DIR/bin:$CHEDDAR_INSTALL_PATH/bin/linux32:/usr/bin/svn:$PATH
export LIBRARY_PATH=$CHEDDAR_INSTALL_PATH/lib/linux32:CHEDDAR_INSTALL_PATH/lib/linux32/gtk-2.0/modules:/lib/i386-linux-gnu/:/usr/lib/i386-linux-gnu:$LIBRARY_PATH
export LD_LIBRARY_PATH=:$LIBRARY_PATH:$LD_LIBRARY_PATH