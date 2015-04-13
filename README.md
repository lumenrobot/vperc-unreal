# vperc
Lumen Virtual Perception: Visualisasi lingkungan berdasarkan data dari seluruh informasi sensor yang ada

## DLL files

* Boost libraries will be dynamically linked (to build, it must be in `C:\local\boost_1_57_0`)
    I tried static link but didn't work, it forces dynamic link.
* `boost_system-vc120-mt-1_57.dll` and `boost_chrono-vc120-mt-1_57.dll` must be copied to `~/git/vperc/Binaries/Win64`
  (need to redo this if you clean/rebuild)
* From `ThirdParty\lib_win64`, `Debug/librabbitmq.4.dll` and `Release/SimpleAmqpClient.2.dll` DLLs must be copied to `~/git/vperc/Binaries/Win64`
  (need to redo this if you clean/rebuild)
