import morphac.examples.constant_controller_example as constant_controller_example


def run_constant_controller_example(robot_type=None):

    if not robot_type:
        robot_type = "ackermann"

    print(
        "The following robot types are supported:\n\t1. ackermann\n\t2. diffdrive\n\t3. dubin\n\t4. tricycle"
    )

    constant_controller_example.run(robot_type)
