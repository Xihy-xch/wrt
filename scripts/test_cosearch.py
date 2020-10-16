#!/usr/bin/env python
#coding=utf-8
# from baselines import deepq
# from baselines.deepq import env_cofind_compare as myenv
# import numpy as np
# seed = 6
# import matplotlib.pyplot as plt
# import datetime as dt
import rospy
from wrt.msg import Situation


class Ship:
    def __init__(self, la, lo):
        self.latitude = la
        self.longitude = lo

    def setLatitudeAndLongitude(self, la, lo):
        self.latitude = la
        self.longitude = lo

ships = []

def situationCallback(msg):
    wrts = msg.wrt_list
    for w in wrts:
        la = w.pos.latitude
        lo = w.pos.longitude
        ship = Ship(la, lo)
        ships.append(ship)

    for ship in ships:
        print(ship.longitude)
        print(ship.latitude)
        func(ship.longitude, ship.latitude)


def func(lo, la):
    action_set = []
    for n in range(8):
        action_set.append(np.array([0. + n * (1. / 9), 1.]))
    action_set.append(np.array([0., 0.]))
    modes = ['rl']
    nums = [[4,2]]
    for num in nums:
        for mode in modes:
            start = dt.datetime.now()
            num_agent, num_target= num
            id_ob = 0
            "接受ros数据"
            for ship in ships:
                print(ship.longitude)
                print(ship.latitude)
            
            ship = Ship()
            ships.append(ship)
            env = myenv(num_agent=num_agent, num_target=num_target, mode=mode, id_ob=id_ob)
            if mode == 'rl':
                model = deepq.learn(
                    env,
                    "conv_only",
                    convs=[(24, 5, 1), (36, 3, 1)],
                    hiddens=[256, 128],
                    dueling=True,
                    total_timesteps=0,
                    load_path='model/find/find12/trainFreq16-{}.pkl'.format(seed) #Python中格式化输出字符串使用format()函数, 字符串即类
                )
            render = False
            max_episode = 50
            episode_steps = []
            finds = []

            for episode in range(1, max_episode+1):
                obs, done = env.reset(), False
                if render:
                    env.reset_graph()
                episode_rews = np.zeros([num_agent,])
                episode_step = 0
                while not done:
                    real_action_set = []
                    actions = None
                    if mode == 'rl':
                        actions = [model(obs[i][None])[0] for i in range(num_agent)]
                        for each in actions:
                            real_action_set.append(action_set[each])
                    #print(real_action_set)
                    obs, rew, done, _ = env.step(actions)
                    "将数据发送出去"
                    episode_rews += rew
                    episode_step += 1
                    if render:
                        env.render()
                find_num = np.sum(env.map_truth + env.map_find == 2) # 两个图中的相同位置的和是否为2,如果为2证明真是地图中的位置和find地图中的位置一致，目标被正确发现

                print("Episode", episode, "; Episode reward", sum(episode_rews), "; Episode step", episode_step, "; Find", find_num)
                finds.append(find_num)
                episode_steps.append(episode_step)
                if render:
                    env.render_result()
            endure = dt.datetime.now() - start
            print("{} agents, {} targets, Policy: {}, Average episode step: {}, Precision: {}%".format(
                num_agent, num_target, mode, np.mean(episode_steps), np.mean(finds)/num_target*100, endure))


if __name__ == '__main__':
    rospy.init_node("node")
    rospy.Subscriber("situationTopic", Situation, situationCallback)
    rospy.spin()
    #main()