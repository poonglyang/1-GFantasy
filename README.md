# 1. 프로젝트 개요
* 팀으로 진행한 MMORPG를 구현 프로젝트입니다
* Unreal 5.4로 제작하였습니다
* 개발 기간 2025.04.19 - 2025.06.24

# 2. 플레이 영상
* AI 파트 - https://youtu.be/DvCc0_7JDXU
* 전체 플레이 흐름 - https://www.youtube.com/watch?v=_T1n5qXT2II
  
# 3. 구현한 기능
## 3.1 전투 시스템
* GAS 기반 타격 피격 시스템
* 피격 방향에 따른 개별 피격 에니메이션
* Evnet로 제작한 QTE
* GAS Ability와 연동되는 Behavior Tree Task
* 다양한 외형에 대응할 수 있는 무기 구현

## 3.2 몬스터
* 소울라이크식 체력바 UI
* 네비가 있는 위치에서만 소환되는 스포너
* BT의 랜덤 일반 공격 
* 자연스러운 사족 보행 애니메이션
* 여러 몬스터의 패턴

## 3.3 Object
* 각 클라이언트에 별도로 동작하는 아이템 상자
* 아이템 드랍
    
## 4. 사용 기술
* C++
* Unreal 5.4.4
* Unreal GAS
* SVN (형상 관리)
* Rider
