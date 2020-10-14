[top]
components : wpump1@WellPump wpump2@WellPump
in : start_in1
in : start_in2
in : stop_in1
in : stop_in2
out : flow_out
Link : start_in1 start_in@wpump1
Link : start_in2 start_in@wpump2
Link : stop_in1 stop_in@wpump1
Link : stop_in2 stop_in@wpump2
Link : flow_out@wpump1 flow_out
Link : flow_out@wpump2 flow_out

[wpump1]
nominal_flow : 250.0

[wpump2]
nominal_flow : 200.0
