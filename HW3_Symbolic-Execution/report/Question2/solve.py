import angr
import claripy

def main():
    project = angr.Project("./example")
    argv1 = claripy.BVS("argv1", 5*8)
    initial_state = project.factory.entry_state(args=["./abc",argv1])
    sm = project.factory.simulation_manager(initial_state)
    sm.explore(find=0x400b0e)
    found = sm.found[0]
    solution = found.solver.eval(argv1, cast_to=bytes)
    print(repr(solution))
    solution = solution[:solution.find(b"\x00")]
    print(solution)
    return solution

if __name__ == '__main__':
    print(repr(main()))
