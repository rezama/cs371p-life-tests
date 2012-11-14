from OpenNero import *
from common import *
import BlocksTower
import random
from BlocksTower.environment import TowerEnvironment
from BlocksTower.constants import *
from copy import copy

###
#
# Action definitions:
# 0 Jump
# 1 Move Forward
# 2 Put Down
# 3 Pick Up
# 4 Rotate Right
# 5 Rotate Left
#
###

class TowerAgent(AgentBrain):
    """
An agent designed to solve Towers of Hanoi
"""
    def __init__(self):
        AgentBrain.__init__(self) # have to make this call
        
    def move(self, frm, to):
        if frm == 'a' and to == 'b': return self.atob
        if frm == 'a' and to == 'c': return self.atoc
        if frm == 'b' and to == 'a': return self.btoa
        if frm == 'b' and to == 'c': return self.btoc
        if frm == 'c' and to == 'a': return self.ctoa
        if frm == 'c' and to == 'b': return self.ctob

    def dohanoi(self, n, to, frm, using):
        if n == 0: return
        prefix = '\t'.join(['' for i in range(self.num_towers - n)])
        strn = "Moving depth {n} from {frm} to {to} using {using}".format(n=n, frm=frm, to=to, using=using)
        for a in self.dohanoi(n-1, using, frm, to):
            yield a
        #self.state.label = strn
        for a in self.move(frm, to):
            yield a
        for a in self.dohanoi(n-1, to, using, frm):
            yield a

    def queue_init(self):
        self.init_queue = [1,5]
        self.atob = [5,1,4,3,4,1,5,2,]
        self.btoa = [3,5,1,4,2,4,1,5,]
        self.atoc = [5,1,4,3,4,1,1,5,2,5,1,4,]
        self.ctoa = [4,1,5,3,5,1,1,4,2,4,1,5,]
        self.btoc = [3,4,1,5,2,5,1,4,]
        self.ctob = [4,1,5,3,5,1,4,2,]
        self.end_queue = [0,0,0,5,5,1]

        from module import getMod
        self.num_towers = getMod().num_towers

        #self.state.label = 'Starting to Solve!'
        for a in self.init_queue:
            yield a
        for a in self.dohanoi(self.num_towers, 'b', 'a', 'c'):
            yield a
        #self.state.label = 'Problem Solved!'
        for a in self.end_queue:
            yield a

    def initialize(self,init_info):
        # Create new Agent
        self.action_info = init_info.actions
        return True
        
    def display_planner(self):
        """ show planner internals by running it externally """
        import subprocess
        # solve for show (user can click through)
        subproc = subprocess.Popen(['python', 'BlocksTower/recursive_solver.py'], stdout=subprocess.PIPE)
        plan = ''
        while True:
            try:
                out = subproc.stdout.read(1)
            except:
                break
            if out == '':
                break
            else:
                plan += out
        print plan

    def start(self, time, sensors):
        """
return first action given the first observations
"""
        self.display_planner()
        self.action_queue = self.queue_init()
        return self.action_queue.next()

    def reset(self):
        self.display_planner()
        self.action_queue = self.queue_init()
        return True

    def act(self, time, sensors, reward):
        """
return an action given the reward for the previous action and the new observations
"""
        try:
            return self.action_queue.next()
        except:
            return 1

    def end(self, time, reward):
        """
receive the reward for the last observation
"""
        print "Final reward: %f, cumulative: %f" % (reward[0], self.fitness[0])
        return True

    def destroy(self):
        """
called when the agent is done
"""
        return True

class TowerAgent2(AgentBrain):
    """
An agent that uses a STRIPS-like planner to solve the Towers of Hanoi problem
"""
    def __init__(self):
        AgentBrain.__init__(self) # have to make this call
        self.action_queue = [5] # rotate left to reset state first

    def initialize(self,init_info):
        """
Create the agent.
init_info -- AgentInitInfo that describes the observation space (.sensors),
the action space (.actions) and the reward space (.rewards)
"""
        self.action_info = init_info.actions
        return True

    def queue_init(self):
        import strips2
        import towers3 as towers
        import subprocess
        import strips2_show

        # solve for show (user can click through)
        subproc = subprocess.Popen(['python', 'BlocksTower/strips2.py'], stdout=subprocess.PIPE)
        plan = ''
        while True:
            try:
                out = subproc.stdout.read(1)
            except:
                break
            if out == '':
                break
            else:
                plan += out
        # actually solve to get the plan of actions
        plan = strips2.solve(towers.INIT, towers.GOAL, towers.ACTIONS)
        action_queue = [5]
        state = copy(towers.INIT)
        at = towers.Pole1
        for (move, what, frm, to) in plan:
            frm_pole = strips2_show.get_pole(state, frm)
            to_pole = strips2_show.get_pole(state, to)
            print what, frm, to, at, frm_pole, to_pole
            if at != frm_pole:
                action_queue += MOVES[(at, frm_pole)]
            action_queue += CARRY_MOVES[(frm_pole, to_pole)]
            move(state, what, frm, to)
            at = to_pole
        return action_queue

    def start(self, time, observations):
        """
return first action given the first observations
"""
        self.action_queue = self.queue_init()
        return self.action_queue.pop(0)

    def act(self, time, observations, reward):
        """
return an action given the reward for the previous
action and the new observations
"""
        if len(self.action_queue) > 0:
            return self.action_queue.pop(0)
        else:
            return 0

    def end(self, time, reward):
        """
receive the reward for the last observation
"""
        return True

    def reset(self):
        self.action_queue = self.queue_init()
        return True

    def destroy(self):
        """
called when the agent is done
"""
        return True

class TowerAgent3(AgentBrain):
    """
An agent that uses a STRIPS-like planner to solve the Towers of Hanoi problem
"""
    def __init__(self):
        import towers3 as towers
        AgentBrain.__init__(self) # have to make this call
        self.action_queue = [10] # rotate left to reset state first
        self.global_at = towers.Pole1
        self.global_state = copy (towers.INIT)
        self.holding = "Nothing"
    
    def initialize(self,init_info):
        """
Create the agent.
init_info -- AgentInitInfo that describes the observation space (.sensors),
the action space (.actions) and the reward space (.rewards)
"""
        self.action_info = init_info.actions
        return True

    def semantic_parser(self, eng_plan):
        #Write code for simple semantic grammar here
        #Actions should be returned in the following format:
        #1. Mov Object Source Destination
        #2. Pick Object Source
        #3. Put Object Destination
        if len(eng_plan) == 0:
            return 'Error'
        
        if self.is_opennero_format(eng_plan):
            print "Opennero Format: "+eng_plan.strip()+"..."
            return eng_plan.strip()
        #Strict parser (must match sentences found in chart on hw page exactly)
        plan = []
        valid = False # used to check if all parts of action are found
        words = eng_plan.strip().split()
        (command) = words[0]
        
        if command == 'Move':
            if len(words) != 7:
                return 'Error'
                
            plan.append('Mov')
            
            if words[2] != 'lying' or words[3] != 'on' or words[5] != 'to':
                return 'Error'
                
            obj = self.check_object(words[1])
            if obj[1] and obj[0] == 1:  #1st obj: Disk
                plan.append(words[1])
            else:
                return 'Error'
            
            obj = self.check_object(words[4])
            if obj[1]:                  #2nd obj: Pole or Disk
                plan.append(words[4])
            else:
                return 'Error'
            
            obj = self.check_object(words[6])
            if obj[1]:                  #3rd obj: Pole or Disk
                plan.append(words[6])
            else:
                return 'Error'
                
        elif command == 'Pick':
            if len(words) != 6:
                return 'Error'
                
            plan.append('Pick')
                
            if words[1] != 'up' or words[3] != 'lying' or words[4] != 'on':
                return 'Error'
                
            obj = self.check_object(words[2])
            if obj[1] and obj[0] == 1:  #1st obj: Disk
                plan.append(words[2])
            else:
                return 'Error'
            
            obj = self.check_object(words[5])
            if obj[1]:                  #2nd obj: Pole or Disk
                plan.append(words[5])
            else:
                return 'Error'
        
        elif command == 'Put':
            if len(words) != 5:
                return 'Error'
                
            plan.append('Put')
                
            if words[1] != 'down' or words[3] != 'on':
                return 'Error'
                
            obj = self.check_object(words[2])
            if obj[1] and obj[0] == 1:  #1st obj: Disk
                plan.append(words[2])
            else:
                return 'Error'
            
            obj = self.check_object(words[4])
            if obj[1]:                  #2nd obj: Pole or Disk
                plan.append(words[4])
            else:
                return 'Error'
        else:
            return 'Error'
        
        print "PLAN:"+str(plan)
        return ' '.join(plan).strip()
        
    def is_opennero_format(self,sentence):
        if "lying" in sentence or "on" in sentence:
            return False
        return True
        
    def check_object(self, obj):
        """
        Checks to see if a given object exists in towers3
        Returns tuple (obj_type,valid)
        @return obj_type 0 if pole, 1 if disk
        @return valid True if exists in towers3, False otherwise
        """

        obj_info = (obj[:4],int(obj[4]))
        obj_type = -1
        valid = False
        
        if obj_info[0] == 'Pole':
            obj_type = 0
            if obj_info[1] < 4:
                valid = True
            
        if obj_info[0] == 'Disk':
            obj_type = 1
            if obj_info[1] < 4:
                valid = True
        
        return (obj_type, valid)

    def check_validity(self, eng_plan):
        print "..."+eng_plan+"..."
        print "CHECK VALIDITY"
        if eng_plan.strip() == 'Error' or len(eng_plan.strip()) == 0:
            return 'Error'
        
        plan = eng_plan.strip().split()
        command = plan[0]
        
        if command == "Pick":
            if self.holding != "Nothing":
                return 'Error'
            elif not ('On', plan[1], plan[2]) in self.global_state:
                return 'Error'
            elif not ('Clear', plan[1]) in self.global_state:
                return 'Error'
            else:
                self.holding = plan[1]
                return eng_plan
        
        elif command == "Put":
            if self.holding != plan[1]:
                return 'Error'
            elif ('Smaller', plan[2], plan[1]) in self.global_state:
                return 'Error'
            elif not ('Clear', plan[2]) in self.global_state:
                return 'Error'
            else:
                self.holding = "Nothing"
                return eng_plan 
                
        elif command == "Mov":
            if self.check_validity("Pick "+plan[1]+" "+plan[2]) == 'Error':
                return 'Error'
            if self.check_validity("Put "+plan[1]+" "+plan[3]) == 'Error':
                self.holding = "Nothing" #if Pick succeeds but Put fails, hold nothing
                return 'Error'
            return eng_plan
        
        else:
            return 'Error'
        
    
    def queue_init(self):
        import subprocess
        # solve for show (user can click through)
        subproc = subprocess.Popen(['python', 'BlocksTower/text_interface.py'], stdout=subprocess.PIPE)
        plan = ''
        while True:
            try:
                out = subproc.stdout.read(1)
            except:
                break
            if out == '':
                break
            else:
                plan += out
        print plan

        parsed_plan = self.check_validity(self.semantic_parser(plan))
        
        if (self.action_queue == [10]):
                action_queue = [5]
        else:
                action_queue = []

        state = self.global_state
        at = self.global_at
        # use strips2 stuff for translating the output into low level actions
        import strips2
        import towers2 as towers
        import strips2_show
        
        words = parsed_plan.strip().split()
        (command) = words[0]

        if command == 'Mov':
            (what, frm, to) = words[1:]
            frm_pole = strips2_show.get_pole(state, frm)
            to_pole = strips2_show.get_pole(state, to)
            print what, frm, to, at, frm_pole, to_pole
            if at != frm_pole:
                action_queue += MOVES[(at, frm_pole)]
            action_queue += CARRY_MOVES[(frm_pole, to_pole)]
            towers.Move(state, what, frm, to)
            at = to_pole

        elif command == 'Pick':
            (what, frm) = words[1:]
            frm_pole = strips2_show.get_pole(state, frm)
            if at != frm_pole:
                action_queue += MOVES[(at, frm_pole)]
            action_queue += [3] #Pick up
            towers.Move(state, what, frm, frm)
            at = frm_pole

        elif command == 'Put':
            (what, to) = words[1:]
            to_pole = strips2_show.get_pole(state, to)
            if at != to_pole:
                action_queue += MOVES[(at, to_pole)]
            action_queue += [2] #Put Down
            towers.Move(state, what, to, to)
            at = to_pole
        
        elif command == 'Error':
            action_queue += [0] #Jump
            print "Invalid input. Please try again"

        self.global_state = state
        self.global_at = at
        print self.global_state
        return action_queue

    def start(self, time, observations):
        """
return first action given the first observations
"""
        self.action_queue = self.queue_init()
        if len(self.action_queue) > 0:
            return self.action_queue.pop(0)
        else:
            return 0

    def act(self, time, observations, reward):
        """
return an action given the reward for the previous
action and the new observations
"""
        if len(self.action_queue) > 0:
            return self.action_queue.pop(0)
        else:
            self.action_queue = self.queue_init()
            return 0

    def end(self, time, reward):
        """
receive the reward for the last observation
"""
        return True

    def reset(self):
        self.action_queue = self.queue_init()
        return True

    def destroy(self):
        """
called when the agent is done
"""
        return True
