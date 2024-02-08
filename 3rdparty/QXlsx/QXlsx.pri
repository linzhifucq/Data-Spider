########################################
# QXlsx.pri
########################################

QT += core
QT += gui-private


CONFIG += c++11

//以下定义会导致编译器在您使用标记为已弃用的Qt功能时发出警告（具体警告取决于您的编译器）
DEFINES += QT_DEPRECATED_WARNINGS


#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # 禁用所有在Qt 6.0.0之前已弃用的API

isEmpty(QXLSX_PARENTPATH) {
    message( 'QXLSX_PARENTPATH is empty. use default value.' )
    QXLSX_PARENTPATH = $$PWD/../
} else {
    message( 'QXLSX_PARENTPATH is not empty.' )
    message( $${QXLSX_PARENTPATH} )
}

isEmpty(QXLSX_HEADERPATH) {
    message( 'QXLSX_HEADERPATH is empty. use default value.' )
    QXLSX_HEADERPATH = $$PWD/../QXlsx/header/
} else {
    message( 'QXLSX_HEADERPATH is not empty.' )
    message( $${QXLSX_HEADERPATH} )
}

isEmpty(QXLSX_SOURCEPATH) {
    message( 'QXLSX_SOURCEPATH is empty. use default value.' )
    QXLSX_SOURCEPATH = $$PWD/../QXlsx/source/
} else {
    message( 'QXLSX_SOURCEPATH is not empty.' )
    message( $${QXLSX_SOURCEPATH} )
}

INCLUDEPATH += $$PWD
INCLUDEPATH += $${QXLSX_PARENTPATH}
INCLUDEPATH += $${QXLSX_HEADERPATH}

########################################
# source code 

HEADERS += \
$${QXLSX_HEADERPATH}xlsxabstractooxmlfile.h \
$${QXLSX_HEADERPATH}xlsxabstractooxmlfile_p.h \
$${QXLSX_HEADERPATH}xlsxabstractsheet.h \
$${QXLSX_HEADERPATH}xlsxabstractsheet_p.h \
$${QXLSX_HEADERPATH}xlsxcell.h \
$${QXLSX_HEADERPATH}xlsxcellformula.h \
$${QXLSX_HEADERPATH}xlsxcellformula_p.h \
$${QXLSX_HEADERPATH}xlsxcelllocation.h \
$${QXLSX_HEADERPATH}xlsxcellrange.h \
$${QXLSX_HEADERPATH}xlsxcellreference.h \
$${QXLSX_HEADERPATH}xlsxcell_p.h \
$${QXLSX_HEADERPATH}xlsxchart.h \
$${QXLSX_HEADERPATH}xlsxchartsheet.h \
$${QXLSX_HEADERPATH}xlsxchartsheet_p.h \
$${QXLSX_HEADERPATH}xlsxchart_p.h \
$${QXLSX_HEADERPATH}xlsxcolor_p.h \
$${QXLSX_HEADERPATH}xlsxconditionalformatting.h \
$${QXLSX_HEADERPATH}xlsxconditionalformatting_p.h \
$${QXLSX_HEADERPATH}xlsxcontenttypes_p.h \
$${QXLSX_HEADERPATH}xlsxdatavalidation.h \
$${QXLSX_HEADERPATH}xlsxdatavalidation_p.h \
$${QXLSX_HEADERPATH}xlsxdatetype.h \
$${QXLSX_HEADERPATH}xlsxdocpropsapp_p.h \
$${QXLSX_HEADERPATH}xlsxdocpropscore_p.h \
$${QXLSX_HEADERPATH}xlsxdocument.h \
$${QXLSX_HEADERPATH}xlsxdocument_p.h \
$${QXLSX_HEADERPATH}xlsxdrawinganchor_p.h \
$${QXLSX_HEADERPATH}xlsxdrawing_p.h \
$${QXLSX_HEADERPATH}xlsxformat.h \
$${QXLSX_HEADERPATH}xlsxformat_p.h \
$${QXLSX_HEADERPATH}xlsxglobal.h \
$${QXLSX_HEADERPATH}xlsxmediafile_p.h \
$${QXLSX_HEADERPATH}xlsxnumformatparser_p.h \
$${QXLSX_HEADERPATH}xlsxrelationships_p.h \
$${QXLSX_HEADERPATH}xlsxrichstring.h \
$${QXLSX_HEADERPATH}xlsxrichstring_p.h \
$${QXLSX_HEADERPATH}xlsxsharedstrings_p.h \
$${QXLSX_HEADERPATH}xlsxsimpleooxmlfile_p.h \
$${QXLSX_HEADERPATH}xlsxstyles_p.h \
$${QXLSX_HEADERPATH}xlsxtheme_p.h \
$${QXLSX_HEADERPATH}xlsxutility_p.h \
$${QXLSX_HEADERPATH}xlsxworkbook.h \
$${QXLSX_HEADERPATH}xlsxworkbook_p.h \
$${QXLSX_HEADERPATH}xlsxworksheet.h \
$${QXLSX_HEADERPATH}xlsxworksheet_p.h \
$${QXLSX_HEADERPATH}xlsxzipreader_p.h \
$${QXLSX_HEADERPATH}xlsxzipwriter_p.h

SOURCES += \
$${QXLSX_SOURCEPATH}xlsxabstractooxmlfile.cpp \
$${QXLSX_SOURCEPATH}xlsxabstractsheet.cpp \
$${QXLSX_SOURCEPATH}xlsxcell.cpp \
$${QXLSX_SOURCEPATH}xlsxcellformula.cpp \
$${QXLSX_SOURCEPATH}xlsxcelllocation.cpp \
$${QXLSX_SOURCEPATH}xlsxcellrange.cpp \
$${QXLSX_SOURCEPATH}xlsxcellreference.cpp \
$${QXLSX_SOURCEPATH}xlsxchart.cpp \
$${QXLSX_SOURCEPATH}xlsxchartsheet.cpp \
$${QXLSX_SOURCEPATH}xlsxcolor.cpp \
$${QXLSX_SOURCEPATH}xlsxconditionalformatting.cpp \
$${QXLSX_SOURCEPATH}xlsxcontenttypes.cpp \
$${QXLSX_SOURCEPATH}xlsxdatavalidation.cpp \
$${QXLSX_SOURCEPATH}xlsxdatetype.cpp \
$${QXLSX_SOURCEPATH}xlsxdocpropsapp.cpp \
$${QXLSX_SOURCEPATH}xlsxdocpropscore.cpp \
$${QXLSX_SOURCEPATH}xlsxdocument.cpp \
$${QXLSX_SOURCEPATH}xlsxdrawing.cpp \
$${QXLSX_SOURCEPATH}xlsxdrawinganchor.cpp \
$${QXLSX_SOURCEPATH}xlsxformat.cpp \
$${QXLSX_SOURCEPATH}xlsxmediafile.cpp \
$${QXLSX_SOURCEPATH}xlsxnumformatparser.cpp \
$${QXLSX_SOURCEPATH}xlsxrelationships.cpp \
$${QXLSX_SOURCEPATH}xlsxrichstring.cpp \
$${QXLSX_SOURCEPATH}xlsxsharedstrings.cpp \
$${QXLSX_SOURCEPATH}xlsxsimpleooxmlfile.cpp \
$${QXLSX_SOURCEPATH}xlsxstyles.cpp \
$${QXLSX_SOURCEPATH}xlsxtheme.cpp \
$${QXLSX_SOURCEPATH}xlsxutility.cpp \
$${QXLSX_SOURCEPATH}xlsxworkbook.cpp \
$${QXLSX_SOURCEPATH}xlsxworksheet.cpp \
$${QXLSX_SOURCEPATH}xlsxzipreader.cpp \
$${QXLSX_SOURCEPATH}xlsxzipwriter.cpp


########################################
# custom setting for compiler & system

win32-g++ {
    message("compiling for windows g++. mingw or msys or cygwin.")
    INCLUDEPATH += $${QXLSX_HEADERPATH}win32-gcc 
	CONFIG(debug, debug|release) {
	} else {
	}	
}
win32-msvc2013 {
    message("Compiling for Visual Studio 2013")
    INCLUDEPATH += $${QXLSX_HEADERPATH}msvc2013 
	CONFIG(debug, debug|release) {
	} else {
	}		
}
win32-msvc2015 {
    message("Compiling for Visual Studio 2015")
    INCLUDEPATH += $${QXLSX_HEADERPATH}msvc2015 
	CONFIG(debug, debug|release) {
	} else {
	}		
}
win32-msvc2017 {
    message("Compiling for Visual Studio 2017")
    INCLUDEPATH += $${QXLSX_HEADERPATH}msvc2017 
	CONFIG(debug, debug|release) {
	} else {
	}		
}
win32-msvc2019 {
    message("Compiling for Visual Studio 2019")
    INCLUDEPATH += $${QXLSX_HEADERPATH}msvc2019
        CONFIG(debug, debug|release) {
        } else {
        }
}
unix {
   !contains(QT_ARCH, x86_64){
       LIB=lib32
       message("compiling for 32bit linux/unix system")
    } else {
       LIB=lib64
       message("compiling for 64bit linux/unix system")
   }

   INCLUDEPATH += $${QXLSX_HEADERPATH}unix-gcc

    # target.path = /usr/lib
    # INSTALLS += target
	
	CONFIG(debug, debug|release) {
	} else {
	}		
}
mac {
    message("compiling for mac os")
    INCLUDEPATH += $${QXLSX_HEADERPATH}mac
	CONFIG(debug, debug|release) {
	} else {
	}		
}

