def execute(self):
    for uid, pilot in self.get_pilot_oracle().items():

        control_input = pilot.execute(self.state, uid)

        # Making sure that the control input dimensions computed by the pilot
        # are of the correct dimensions.
        assert self.state.get_robot(
            uid).kinematic_model.control_input_size == control_input.size

        updated_robot_state = self.get_integrator(uid).step(
            robot_state=self.state.get_robot_state(uid),
            control_input=control_input,
            dt=self.spec.dt
        )

        # Updating the state of the robot.
        self.state.set_robot_state(updated_robot_state, uid)
