set(Boost_DETAILED_FAILURE_MSG on)
set(Boost_Bootstrap_Command)

if(WIN32)
    set(Boost_Url   "https://vorboss.dl.sourceforge.net/project/boost/boost/1.63.0/boost_1_63_0.zip")
    set(Boost_SHA512  "8e908275847cdce6a9b645da35f59ae3dc1f5874a3a61ad166fe8e34171b10c77bca57102a25797119f4fe428e824f9d34290bfa1f14e9507774c0e97c947c47")
    set(Boost_Bootstrap_Command bootstrap.bat)
    set(Boost_b2_Command b2.exe)
else()
    set(Boost_Url   "https://vorboss.dl.sourceforge.net/project/boost/boost/1.63.0/boost_1_63_0.tar.gz")
    set(Boost_SHA512  "7add6a254dfd5feef9edbfa9fc5aafa2bf41d1623f98970b2d33db892fe95549657a4ba2934d972793816682e9152463a33b78b3c69f053091528326880fe8e9")
    set(Boost_Bootstrap_Command ./bootstrap.sh)
    set(Boost_b2_Command ./b2)
endif()

set(Config_Libraries "log,program_options")

include(ExternalProject)
ExternalProject_Add(Boost
    TMP_DIR "${RAYON_ROOT_DIR}/downloads/tmp"
    DOWNLOAD_DIR "${RAYON_ROOT_DIR}/downloads"
    URL "${Boost_Url}"
    URL_HASH "SHA512=${Boost_SHA512}"
    SOURCE_DIR ${RAYON_ROOT_DIR}/downloads/boost_1_63_0
    BUILD_IN_SOURCE 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ${Boost_Bootstrap_Command}
    --without-icu
    --with-libraries=${Config_Libraries}
    "--prefix=${RAYON_ROOT_DIR}/Dependencies/boost_1_63_0"
    BUILD_COMMAND  ${Boost_b2_Command}
    --without-python
    --address-model=64
    --architecture=x64
    --threading=multi
    --link=shared
    --layout=tagged
    --build-type=complete
    -j4
    INSTALL_COMMAND ${Boost_b2_Command}
    --without-python
    --address-model=64
    --architecture=x64
    --threading=multi
    --link=shared
    --layout=tagged
    --build-type=complete
    -j4 install
    INSTALL_DIR "${RAYON_ROOT_DIR}/Dependencies/boost_1_63_0"
    LOG_DOWNLOAD 1
    LOG_UPDATE 1
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_TEST 1
    LOG_INSTALL 1
    )