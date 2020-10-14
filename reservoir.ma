[top]
components : res@Reservoir
in : q_in
in : qp_in
out : level_out
out : low_level_out
Link : q_in q_in@res
Link : qp_in qp_in@res
Link : level_out@res level_out
Link : low_level_out@res low_level_out

[res]
alarm_level : 0.5
