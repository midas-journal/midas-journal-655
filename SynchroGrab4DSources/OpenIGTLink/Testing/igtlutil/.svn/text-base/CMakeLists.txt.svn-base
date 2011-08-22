ADD_EXECUTABLE(igtl_image_test igtl_image_test.c)
ADD_EXECUTABLE(igtl_header_test igtl_header_test.c)
ADD_EXECUTABLE(igtl_transform_test igtl_transform_test.c)
ADD_EXECUTABLE(igtl_util_test igtl_util_test.c)

TARGET_LINK_LIBRARIES(igtl_image_test OpenIGTLink)
TARGET_LINK_LIBRARIES(igtl_header_test OpenIGTLink)
TARGET_LINK_LIBRARIES(igtl_transform_test OpenIGTLink)
TARGET_LINK_LIBRARIES(igtl_util_test OpenIGTLink)

ADD_TEST( igtl_image_test_01     ${OpenIGTLink_EXECUTABLE_PATH}/igtl_image_test )
ADD_TEST( igtl_header_test_01    ${OpenIGTLink_EXECUTABLE_PATH}/igtl_header_test )
ADD_TEST( igtl_transform_test_01 ${OpenIGTLink_EXECUTABLE_PATH}/igtl_transform_test )
ADD_TEST( igtl_util_test_01      ${OpenIGTLink_EXECUTABLE_PATH}/igtl_util_test )

