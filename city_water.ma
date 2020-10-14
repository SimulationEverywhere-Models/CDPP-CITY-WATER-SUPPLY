[top]
components : pump1@Pump
components : pump2@Pump
components : res@Reservoir
components : wpump1@WellPump
components : wpump2@WellPump
in : start_in1
in : stop_in1
in : start_in2
in : stop_in2
in : wstart_in1
in : wstop_in1
in : wstart_in2
in : wstop_in2
in : power_in
out : flow_out
out : state_out1
out : state_out2
out : level
Link : power_in power_in@pump1
Link : power_in power_in@pump2
Link : start_in1 start_in@pump1
Link : start_in2 start_in@pump2
Link : stop_in1 stop_in@pump1
Link : stop_in2 stop_in@pump2
Link : wstart_in1 start_in@wpump1
Link : wstop_in1 stop_in@wpump1
Link : wstart_in2 start_in@wpump2
Link : wstop_in2 stop_in@wpump2
Link : level_out@res level_in@pump1
Link : level_out@res level_in@pump2
Link : level_out@res level
Link : flow_out@wpump1 q_in@res
Link : flow_out@wpump2 q_in@res
Link : state_out@pump1 state_out1
Link : state_out@pump2 state_out2
Link : flow_out@pump1 flow_out
Link : flow_out@pump2 flow_out
Link : flow_out@pump1 qp_in@res
Link : flow_out@pump2 qp_in@res
Link : low_level_out@res low_level_in@pump1
Link : low_level_out@res low_level_in@pump2

[pump1]
nominal_flow : 250.0
alarm_level : 0.5

[pump2]
nominal_flow : 225.0
alarm_level : 0.5

[wpump1]
nominal_flow : 175.0

[wpump2]
nominal_flow : 200.0

[res]
alarm_level : 0.5
