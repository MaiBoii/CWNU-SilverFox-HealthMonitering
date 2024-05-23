# 작성자: 마승욱
# 작성일: 
# Silverfox 보행보조차 제어부에서 사용되는 함수들을 모아놓은 파일입니다.
import random
from models import db, Profile, Workout
from faker import Faker
from datetime import datetime,time, timedelta

fake = Faker('ko_KR')

# # 오늘치 workout 데이터에 today_weight의 값이 있으면 True, 없으면 False
# def isThereTodayWeight(mycursor, mydb):
#     mycursor.execute("SELECT today_weight FROM workout WHERE today_weight = 0.0 AND date=CURDATE()")
#     myresult = mycursor.fetchall()
#     if myresult:
#         return True
#     else:
#         return False

# # 오늘치 workout 데이터에 distance의 값이 있으면 True, 없으면 False
# def isThereTodayDistance(mycursor, mydb):
#     mycursor.execute("SELECT today_distance FROM workout WHERE today_distance = 0.0 AND date=CURDATE()")
#     myresult = mycursor.fetchall()
#     if myresult:
#         return True
#     else:
#         return False
    
# # 오늘치 workout 데이터에 time의 값이 있으면 True, 없으면 False
# def isThereTodayTime(mycursor, mydb):
#     mycursor.execute("SELECT today_time FROM workout WHERE today_time = 00:00:00 AND date=CURDATE()")
#     myresult = mycursor.fetchall()
#     if myresult:
#         return True
#     else:
#         return False

# # 오늘치 workout 데이터가 있으면 True, 없으면 False
# def isThereTodayWorkout(mycursor, mydb):
#     mycursor.execute("SELECT * FROM workout WHERE date=CURDATE()")
#     myresult = mycursor.fetchall()
#     if myresult:
#         return True
#     else:
#         return False

def create_dummy_data():
    # 시작 날짜와 끝 날짜 정의
    start_date = datetime(2024, 9, 2)
    end_date = datetime(2024, 10, 1)

    # 기존 데이터가 있는지 확인
    existing_data = Workout.query.filter(Workout.date.between(start_date, end_date)).first()

    # 기존 데이터가 없을 때만 데이터 생성
    if not existing_data:
        # 날짜를 하루씩 증가시키면서 데이터 생성
        current_date = start_date
        while current_date <= end_date:
            workout = Workout(
                date=current_date.strftime('%Y-%m-%d'),
                distance=round(random.uniform(1.0, 10.0), 1),
                workout_time=time(random.randint(0, 2), random.randint(0, 59)),
                today_weight=round(random.uniform(50,55), 1),
                oxygen=random.randint(90, 100),
                temp=round(random.uniform(35.5, 37.5), 1),
                heart=random.uniform(60.0, 120.0)
            )
            db.session.add(workout)
            db.session.commit()
            # 다음 날짜로 이동
            current_date += timedelta(days=1)