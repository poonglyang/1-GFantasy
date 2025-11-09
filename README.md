# 1. 프로젝트 개요
* 팀으로 진행한 MMORPG를 구현 프로젝트입니다
* GAS기반 시스템과 AI 몬스터를 담당하였습니다
* Unreal 5.4로 제작하였습니다
* 개발 기간 2025.04.19 - 2025.06.24

# 2. 플레이 영상
* AI 파트 - https://youtu.be/DvCc0_7JDXU
* 전체 플레이 흐름 - https://www.youtube.com/watch?v=_T1n5qXT2II
  
# GFantasy - Unreal Engine 프로젝트

## 📋 프로젝트 개요

GFantasy는 Unreal Engine 5를 기반으로 한 액션 RPG 게임 프로젝트입니다. Gameplay Ability System(GAS)을 활용한 스킬 시스템과 Behavior Tree 기반 NPC AI 시스템을 구현한 멀티플레이어 게임입니다.

## 📁 프로젝트 구조

### 1. Character (캐릭터 시스템)

#### `GASBaseCharacter.h` / `GASBaseCharacter.cpp`
- **역할**: 모든 캐릭터의 기본 클래스
- **기능**: 
  - Gameplay Ability System 인터페이스 구현
  - AbilitySystemComponent 접근 제공
  - 기본 캐릭터 동작 정의

#### `GASPlayerCharacter.h` / `GASPlayerCharacter.cpp`
- **역할**: 플레이어 캐릭터 전용 클래스
- **기능**:
  - 입력 처리 (Enhanced Input)
  - 타겟팅 시스템
  - 무기 장착/해제
  - 탈것 시스템
  - 커스터마이징

#### `GASCombatNPC.h` / `GASCombatNPC.cpp`
- **역할**: 전투 NPC (적 캐릭터) 클래스
- **기능**:
  - GAS 기반 전투 시스템
  - AbilitySystemComponent 및 AttributeSet 관리
  - 데미지 처리 (일반/강공격)
  - 히트 리액션 시스템
  - 사망 처리 (Ragdoll, 디졸브 효과)
  - 포커스 모드 관리 (HP바, 이름 표시)
  - 슈퍼아머 시스템
  - 아이템 드롭 시스템
  - EnemyInterface 구현

### 2. Controller (컨트롤러 시스템)

#### `GASWorldPlayerController.h` / `GASWorldPlayerController.cpp`
- **역할**: 월드 레벨의 플레이어 컨트롤러
- **기능**:
  - 보스 UI 바인딩
  - 입력 컨텍스트 관리

#### `AIControllerBase.h` / `AIControllerBase.cpp`
- **역할**: AI 컨트롤러의 기본 클래스
- **기능**:
  - Behavior Tree 실행 및 관리
  - AI Perception 시스템 (시야, 청각, 데미지 감지)
  - 적 상태 관리 (EEnemyState)
  - 포커스 액터 관리
  - 회전 모드 제어
  - 패턴 타이머 시스템

#### `GASEnemyAIController.h` / `GASEnemyAIController.cpp`
- **역할**: 적 NPC 전용 AI 컨트롤러
- **기능**: GAS 기반 적 AI 행동 제어

### 3. AI & Behavior Tree (AI 시스템)

#### Behavior Tree Task (BTT)
Behavior Tree에서 실행되는 태스크 노드들:

- **`BTTAbilityToOwner.h` / `BTTAbilityToOwner.cpp`**
  - GAS 어빌리티를 NPC에게 실행시키는 태스크
  - 어빌리티 태그 기반 실행
  - 데드락 방지 타이머

- **`BTT_SelectFocus.h` / `BTT_SelectFocus.cpp`**
  - 포커스할 타겟을 선택하는 태스크

- **`BTT_ChangeEnemyState.h` / `BTT_ChangeEnemyState.cpp`**
  - 적의 상태를 변경하는 태스크

- **`BTT_DetectFocusActorByTick.h` / `BTT_DetectFocusActorByTick.cpp`**
  - 틱마다 포커스 액터를 감지하는 태스크

- **`BTT_MoveRound.h` / `BTT_MoveRound.cpp`**
  - 원형 이동 패턴 태스크

- **`BTT_PatternTimer.h` / `BTT_PatternTimer.cpp`**
  - 패턴 타이머 관리 태스크

- **`BTT_RandomLocation.h` / `BTT_RandomLocation.cpp`**
  - 랜덤 위치 생성 태스크

- **`BTT_MontageCancle.h` / `BTT_MontageCancle.cpp`**
  - 애니메이션 몽타주 취소 태스크

- **`BTT_ChangeRotateMode.h` / `BTT_ChangeRotateMode.cpp`**
  - 회전 모드 변경 태스크

- **`BTT_ChangeUseSense.h` / `BTT_ChangeUseSense.cpp`**
  - 감지 시스템 사용 여부 변경 태스크

- **`BTT_GiveGameplayTag.h` / `BTT_GiveGameplayTag.cpp`**
  - GameplayTag 부여 태스크

#### Behavior Tree Decorator (BTD)
Behavior Tree의 조건 판단 노드들:

- **`BTD_HasTag.h` / `BTD_HasTag.cpp`**
  - NPC가 특정 GameplayTag를 가지고 있는지 확인하는 데코레이터
  - GAS 태그 시스템과 연동

### 4. GAS (Gameplay Ability System)

#### `GASCBase.h` / `GASCBase.cpp`
- **역할**: Ability System Component의 기본 클래스
- **기능**: 스킬 시스템의 핵심 컴포넌트

#### `GASBasePlayerState.h` / `GASBasePlayerState.cpp`
- **역할**: 플레이어 상태 관리
- **기능**:
  - AttributeSet 관리 (체력, 공격력 등)
  - AbilitySystemComponent 소유
  - 초기 스탯 설정

#### Enemy GameplayAbility (적 어빌리티)
적 NPC가 사용하는 GAS 어빌리티들:

- **`GA_GroundLoopBase.h` / `GA_GroundLoopBase.cpp`**
  - 지면 루프 패턴 기본 클래스
  - 타겟 체력 바인딩 기능

- **`GA_SuccubusPattern1.h` / `GA_SuccubusPattern1.cpp`**
  - 서큐버스 보스 패턴 1 어빌리티
  - 원형 데칼 패턴 생성
  - 안전 지역/위험 지역 표시
  - 서큐버스 볼 생성 및 폭발 시스템

- **`GA_SuccubusPhase2Attack2.h` / `GA_SuccubusPhase2Attack2.cpp`**
  - 서큐버스 2페이즈 공격 패턴 2
  - 낫 오라 스폰 위치 계산

- **`GA_SuccubusPhase2Attack3.h` / `GA_SuccubusPhase2Attack3.cpp`**
  - 서큐버스 2페이즈 공격 패턴 3
  - 공격 스폰 위치 계산

#### Succubus 보스 시스템

- **`BossSuccubusCharacter.h` / `BossSuccubusCharacter.cpp`**
  - 서큐버스 보스 캐릭터 클래스
  - 페이즈 전환 시스템
  - 애니메이션 인스턴스 변경
  - 메시 변경 (2페이즈)

- **`BossSuccubusAIController.h` / `BossSuccubusAIController.cpp`**
  - 서큐버스 보스 AI 컨트롤러
  - 보스 영역 내 플레이어 관리
  - 그로기 시스템
  - 페이즈 2 전환 로직
  - 힐링 효과 관리

- **`SuccubusCircleDeca.h` / `SuccubusCircleDeca.cpp`**
  - 서큐버스 원형 데칼 액터
  - 안전/위험 지역 표시
  - 서큐버스 볼 스폰 및 관리
  - 플레이어 감지 및 폭발 처리

- **`SuccubusBall.h` / `SuccubusBall.cpp`**
  - 서큐버스 볼 액터
  - 타임라인 기반 상승 애니메이션
  - 폭발 이펙트 처리
  - 데미지 적용

## 🤖 NPC 시스템 아키텍처

### CombatNPC와 Behavior Tree 연동 구조

```
AIControllerBase (AI 컨트롤러)
    ↓
Behavior Tree (행동 트리)
    ├── BTT (Behavior Tree Task) - 실행 태스크
    │   ├── BTTAbilityToOwner - GAS 어빌리티 실행
    │   ├── BTT_SelectFocus - 타겟 선택
    │   ├── BTT_ChangeEnemyState - 상태 변경
    │   └── ...
    └── BTD (Behavior Tree Decorator) - 조건 판단
        └── BTD_HasTag - GameplayTag 확인
            ↓
GASCombatNPC (전투 NPC)
    ├── AbilitySystemComponent
    ├── AttributeSet (체력, 공격력 등)
    └── GameplayAbility (스킬)
```

### AI Perception 시스템

- **시야 감지 (Sight)**: 플레이어 시각적 감지
- **청각 감지 (Hearing)**: 소리 기반 감지
- **데미지 감지 (Damage)**: 데미지 받은 위치 감지

## 🔄 헤더와 cpp 파일의 관계

### 분리하는 이유

1. **컴파일 시간 단축**: 헤더가 변경되지 않으면 cpp만 재컴파일
2. **의존성 관리**: 헤더는 인터페이스, cpp는 구현
3. **가독성 향상**: 선언과 구현의 명확한 분리
4. **순환 참조 방지**: 전방 선언 활용 가능

### Unreal Engine 특수성

- **UCLASS()**: 헤더에 선언, 리플렉션 시스템에 등록
- **UFUNCTION()**: 블루프린트에서 호출 가능한 함수
- **UPROPERTY()**: 에디터에서 편집 가능한 변수
- **GENERATED_BODY()**: Unreal Header Tool이 자동 생성하는 코드

## 📝 파일 작성 가이드라인

### 헤더 파일 작성 시
- ✅ 필요한 전방 선언만 포함
- ✅ 최소한의 include만 사용
- ✅ 클래스 선언과 기본 구조만 포함
- ✅ 주석으로 클래스 역할 명시

### 구현 파일 작성 시
- ✅ 필요한 모든 헤더 include
- ✅ 실제 로직 구현
- ✅ 델리게이트 바인딩

## 🎮 주요 기능

- **GAS 기반 스킬 시스템**: 다양한 스킬과 어빌리티 구현
  - Enemy 어빌리티: 적 NPC 전용 패턴 어빌리티
  - Succubus 보스 패턴: 원형 데칼 기반 공격 패턴 시스템
- **NPC & AI 시스템**: Behavior Tree 기반 AI 행동 제어
  - CombatNPC: 전투 NPC 시스템
  - Behavior Tree Task: 다양한 AI 행동 패턴
  - Behavior Tree Decorator: 조건 기반 행동 분기
  - AI Perception: 시야, 청각, 데미지 감지
  - 보스 AI: 페이즈 전환, 그로기 시스템
- **멀티플레이어**: 서버-클라이언트 아키텍처

## 📚 참고 자료

- [Unreal Engine 공식 문서](https://docs.unrealengine.com/)
- [Gameplay Ability System 문서](https://github.com/tranek/GASDocumentation)
- [Unreal Engine Behavior Tree 가이드](https://docs.unrealengine.com/en-US/InteractiveExperiences/ArtificialIntelligence/BehaviorTrees/)

## 📄 라이선스

이 프로젝트는 Unreal Engine의 표준 라이선스를 따릅니다.

---

**작성일**: 2024  
**엔진 버전**: Unreal Engine 5.x  
**언어**: C++

