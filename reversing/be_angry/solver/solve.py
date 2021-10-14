#!/usr/bin/env python3
import angr
import logging

logging.getLogger("angr").setLevel("CRITICAL")
angr.manager.l.setLevel("CRITICAL")
proj = angr.Project("./chall")

simgr = proj.factory.simgr()
simgr.explore(find=lambda s: b"Correct" in s.posix.dumps(1))
if len(simgr.found) > 0:
    found = simgr.found[0].posix.dumps(0).decode("utf-8", "ignore")
    print(found)
