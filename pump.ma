[top]
components : pump1@Pump pump2@Pump
in : start_in1
in : start_in2
in : stop_in1
in : stop_in2
in : level_in
in : low_level_in
in : power_in
out : state_out1
out : state_out2
out : flow_out
Link : start_in1 start_in@pump1
Link : start_in2 start_in@pump2
Link : stop_in1 stop_in@pump1
Link : stop_in2 stop_in@pump2
Link : level_in level_in@pump1
Link : low_level_in low_level_in@pump1
Link : power_in power_in@pump1
Link : level_in level_in@pump2
Link : low_level_in low_level_in@pump2
Link : power_in power_in@pump2
Link : state_out@pump1 state_out1
Link : flow_out@pump1 flow_out
Link : state_out@pump2 state_out2
Link : flow_out@pump2 flow_out

[pump1]
nominal_flow : 250.0
alarm_level : 0.5

[pump2]
nominal_flow : 200.0
alarm_level : 0.4

