from flask_sqlalchemy import SQLAlchemy
from datetime import date, time
#from sqlalchemy.ext.declarative import declarative_base
db = SQLAlchemy()

# 사용자 정보 모음 
class Profile(db.Model):
        member_id = db.Column(db.Integer, primary_key=True)
        name = db.Column(db.VARCHAR(10))
        age = db.Column(db.Integer)
        height = db.Column(db.Integer)
        init_weight = db.Column(db.Integer)

# 일일 건강 모니터링 정보 모음
class Workout(db.Model):
        workout_id = db.Column(db.Integer, primary_key =True)
        date = db.Column(db.Date)
        distance = db.Column(db.Float)
        workout_time = db.Column(db.Time)
        today_weight = db.Column(db.Float)
        oxygen = db.Column(db.Integer)
        temp = db.Column(db.Float)
        heart = db.Column(db.Integer)

#avg 테이블
class avg(db.Model):
   id = db.Column(db.Integer, primary_key=True)
   avg_exer = db.Column(db.Float)
   avg_time = db.Column(db.Time)
   avg_weight = db.Column(db.Float)

class month_avg(db.Model):
   id = db.Column(db.Integer, primary_key=True)
   avg_exer = db.Column(db.Float)
   avg_time = db.Column(db.Time)
   avg_weight = db.Column(db.Float)
   
# 한달 평균 들어갈 테이블 12개월치
class Year(db.Model):
   id = db.Column(db.Integer, primary_key=True)
   date = db.Column(db.Date)
   distance = db.Column(db.Float)
   workout_time = db.Column(db.Time)
   today_weight = db.Column(db.Float)
   oxygen = db.Column(db.Integer)
   temp = db.Column(db.Float)
   heart = db.Column(db.Integer)

class Token(db.Model):
     id = db.Column(db.Integer, primary_key=True)
     token = db.Column(db.Text)