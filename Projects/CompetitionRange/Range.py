import pandas as pd
import random
import math
import xlrd
from xlutils.copy import copy

TeamFile = 'Teams.xls'
GroupFile = 'Groups.xls'
GameFile = 'Games.xls'


def writegame(Game, row, port, ws):
    ws.write(row, 0, str(row))
    ws.write(0, 3 * port + 1, '红方' + str(port + 1))
    ws.write(row, 3 * port + 1, str(Game['Red']['SchoolName']) + "\n" + str(Game['Red']['TeamName']))
    ws.write(0, 3 * port + 2, '蓝方' + str(port + 1))
    ws.write(row, 3 * port + 2, str(Game['Blue']['SchoolName']) + "\n" + str(Game['Blue']['TeamName']))


# 获取各个战队
df = pd.read_excel(TeamFile)
Teams = []
EmptyTeam = {'SchoolName': '', 'TeamName': ''}
for item, data in df.iterrows():
    Teams.append({'SchoolName': data.at['学校名称'], 'TeamName': data.at['战队名称']})

# 将战队分组, 每组最多四个战队
Groups = []
EmptyGroup = {'Team1': EmptyTeam, 'Team2': EmptyTeam, 'Team3': EmptyTeam, 'Team4': EmptyTeam}
for i in range(math.ceil(len(Teams) / 4)):
    if 4 * i + 4 <= len(Teams):
        Groups.append({'Team1': Teams[4 * i + 0], 'Team2': Teams[4 * i + 1],
                       'Team3': Teams[4 * i + 2], 'Team4': Teams[4 * i + 3]})
    elif 4 * i + 3 == len(Teams):
        Groups.append({'Team1': Teams[4 * i + 0], 'Team2': Teams[4 * i + 1],
                       'Team3': Teams[4 * i + 2], 'Team4': EmptyTeam})
    elif 4 * i + 2 == len(Teams):
        Groups.append({'Team1': Teams[4 * i + 0], 'Team2': Teams[4 * i + 1],
                       'Team3': EmptyTeam, 'Team4': EmptyTeam})
    elif 4 * i + 1 == len(Teams):
        Groups.append({'Team1': Teams[4 * i + 0], 'Team2': EmptyTeam,
                       'Team3': EmptyTeam, 'Team4': EmptyTeam})

# 将分组情况写到 Excel 表格中
rb = xlrd.open_workbook(GroupFile, formatting_info=True)
wb = copy(rb)  # 复制页面
ws = wb.get_sheet(0)  # 取第一个sheet
ws.write(0, 0, '序号')
ws.write(0, 1, '学校名')
ws.write(0, 2, '战队名')
ws.write(0, 3, '分组')
for i in range(len(Groups)):
    ws.write(4 * i + 1, 0, 4 * i + 1)
    ws.write(4 * i + 2, 0, 4 * i + 2)
    ws.write(4 * i + 3, 0, 4 * i + 3)
    ws.write(4 * i + 4, 0, 4 * i + 4)

    ws.write(4 * i + 1, 1, Groups[i]['Team1']['SchoolName'])
    ws.write(4 * i + 1, 2, Groups[i]['Team1']['TeamName'])

    ws.write(4 * i + 2, 1, Groups[i]['Team2']['SchoolName'])
    ws.write(4 * i + 2, 2, Groups[i]['Team2']['TeamName'])

    ws.write(4 * i + 3, 1, Groups[i]['Team3']['SchoolName'])
    ws.write(4 * i + 3, 2, Groups[i]['Team3']['TeamName'])

    ws.write(4 * i + 4, 1, Groups[i]['Team4']['SchoolName'])
    ws.write(4 * i + 4, 2, Groups[i]['Team4']['TeamName'])

    ws.write(4 * i + 1, 3, i + 1)
    ws.write(4 * i + 2, 3, i + 1)
    ws.write(4 * i + 3, 3, i + 1)
    ws.write(4 * i + 4, 3, i + 1)
wb.save(GroupFile)  # 保存文件

# 开始进行对战的排布
EmptyGame = {'Red': EmptyTeam, 'Blue': EmptyTeam}
games = []

# 先以数字代表战队模拟排序
team = 0  # 组内战队号
group = 0  # 组号
grouptime = 0  # 该小组出现的次数
for i in range(10 * 8):
    if team == 2:
        group += 1
        team = 0
        if group == len(Groups):
            group = 0
            grouptime += 1

    if grouptime == 3:
        games.append(())
        continue

    if team == 0:
        games.append((0, 1, group, grouptime))
        team += 1
    else:
        games.append((2, 3, group, grouptime))
        team += 1
Games = []
for i in range(10):
    gamegroup = []
    for j in range(8):
        gamegroup.append(games[j + 8 * i])
    random.shuffle(gamegroup)
    Games.append(gamegroup)
    print(gamegroup)

# 将模拟排序的战队写入 Excel
rb = xlrd.open_workbook(GameFile, formatting_info=True)
wb = copy(rb)  # 复制页面
ws = wb.get_sheet(0)  # 取第一个sheet
row = 0
for group in Games:
    row += 1
    port = 0
    for game in group:
        if game != ():
            if game[3] == 0:
                if game[0] == 0:
                    writegame({'Red': Groups[game[2]]['Team2'], 'Blue': Groups[game[2]]['Team1']}, row, port, ws)
                else:
                    writegame({'Red': Groups[game[2]]['Team3'], 'Blue': Groups[game[2]]['Team4']}, row, port, ws)
            elif game[3] == 1:
                if game[0] == 0:
                    writegame({'Red': Groups[game[2]]['Team1'], 'Blue': Groups[game[2]]['Team3']}, row, port, ws)
                else:
                    writegame({'Red': Groups[game[2]]['Team2'], 'Blue': Groups[game[2]]['Team4']}, row, port, ws)
            elif game[3] == 2:
                if game[0] == 0:
                    writegame({'Red': Groups[game[2]]['Team4'], 'Blue': Groups[game[2]]['Team1']}, row, port, ws)
                else:
                    writegame({'Red': Groups[game[2]]['Team2'], 'Blue': Groups[game[2]]['Team3']}, row, port, ws)
        else:
            writegame(EmptyGame, row, port, ws)
        port += 1
wb.save(GameFile)  # 保存文件
