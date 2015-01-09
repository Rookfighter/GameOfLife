if( ${CATCH_FOUND} )

else( ${CATCH_FOUND} )
    message(STATUS "  Catch not found, not tests will be built")
endif( ${CATCH_FOUND} )