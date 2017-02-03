function(prefix_custom_list output_result input_prefix input_list)
  foreach(val ${${input_list}})
    set(FUNCTION_RESULT "${FUNCTION_RESULT};${input_prefix}${val}")
  endforeach(val)
  set(${output_result} ${FUNCTION_RESULT} PARENT_SCOPE)
endfunction(prefix_custom_list)

macro(GroupSources Sources PathPrefix SourcePrefix)
    foreach(child ${${Sources}})
        SET(groupname ${SourcePrefix}/${child})
        string(REGEX REPLACE "/[^/]+$" "" groupname ${groupname})
        string(REPLACE "/" "\\" groupname ${groupname})
        source_group(${groupname} FILES ${PathPrefix}/${child})
    endforeach()
endmacro()