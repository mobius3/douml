set QMAKE=qmake
set MAKE=mingw32-make
set SRC_DIRS=src src/CppGenerator src/CppReverse src/CppRoundtrip src/JavaGenerator src/JavaReverse src/JavaRoundtrip src/JavaCat src/PhpGenerator src/PhpReverse src/PythonGenerator src/IdlGenerator src/PlugOutUpgrade src/RoundtripBody
set PLUGOUT_DIRS=genplugouts/html/cpp genplugouts/gpro genplugouts/import_rose genplugouts/singleton/cpp genplugouts/cpp_utilities genplugouts/xmi genplugouts/xmi2 genplugouts/xmi2import genplugouts/sm/cpp genplugouts/usecasewizard/cpp genplugouts/sort/cpp genplugouts/uml_projection/cpp genplugouts/file_control genplugouts/deploy/cpp genplugouts/global_change

set PROGS=src\release\douml.exe src\CppGenerator\release\cpp_generator.exe src\CppReverse\release\cpp_reverse.exe src\CppRoundtrip\release\cpp_roundtrip.exe src\JavaGenerator\release\java_generator.exe src\JavaReverse\release\java_reverse.exe src\JavaRoundtrip\release\java_roundtrip.exe src\JavaCat\release\java_catalog.exe src\PhpGenerator\release\php_generator.exe src\PhpReverse\release\php_reverse.exe src\PythonGenerator\release\python_generator.exe src\IdlGenerator\release\idl_generator.exe src\PlugOutUpgrade\release\plug_out_upgrade.exe src\RoundtripBody\release\roundtrip_body.exe genplugouts\html\cpp\release\ghtml.exe genplugouts\gpro\release\gpro.exe genplugouts\import_rose\release\irose.exe genplugouts\cpp_utilities\release\cpp_util.exe genplugouts\xmi\release\gxmi.exe genplugouts\xmi2\release\gxmi2.exe genplugouts\xmi2import\release\ixmi2.exe genplugouts\sm\cpp\release\stmgen.exe genplugouts\usecasewizard\cpp\release\usecasewizard.exe genplugouts\sort\cpp\release\browsersort.exe genplugouts\uml_projection\cpp\release\uml_proj.exe genplugouts\release\file_control\release\file_control.exe genplugouts\deploy\cpp\release\deplcl.exe genplugouts\global_change\release\global_change.exe

for %%i in (%SRC_DIRS%) do (
	set PWD=%CD%
	cd %%i
	%QMAKE%
	%MAKE%
	cd %PWD%
)
for %%i in (%PLUGOUT_DIRS%) do (
	set PWD=%CD%
	cd %%i
	%QMAKE%
	%MAKE%
	cd %PWD%
)

for %%i in (%PROGS%) do (
	copy "%%i" release

)
