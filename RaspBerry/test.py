import schedule
import time

def print_test():
    print("test word")


if __name__ == '__main__':

    print("실행")

    # 현재 시간대로 스케줄러 작업 등록
    schedule.every().day.at("13:10:30").do(print_test)
    schedule.every().day.at("13:09:55").do(print_test)


    # 계속해서 스케줄러된 작업을 실행
    while True:
        schedule.run_pending()
        time.sleep(1)  # 1분마다 스케줄링된 작업을 확인합니다.

    