#!/usr/bin/env python3
import angr
import logging

angr.manager.l.setLevel("CRITICAL")
logging.getLogger("angr").setLevel("CRITICAL")
logging.getLogger("angr.analysis").setLevel("CRITICAL")
proj = angr.Project("./chal")

while True:
    simgr = proj.factory.simgr()
    simgr.explore(find=lambda s: b"Correct" in s.posix.dumps(1))
    found = simgr.found[0].posix.dumps(0).decode("utf-8", "ignore")
    print(found)
    exit(0)
