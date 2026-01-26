# 🚀 Dungeon Escape (Unreal Engine 5.6 C++)
**Udemy의 'Unreal Engine 5 C++ Developer' 과정을 기반으로 확장 제작된 1인칭 던전 탈출 퍼즐 게임입니다.** 기본적인 물리 상호작용을 넘어, 포인터(Pointer)와 캐스팅(Casting)을 활용한 객체 간 참조, 이벤트 기반의 트리거 시스템, 그리고 레벨 디자인과 조명 연출을 통해 완성도 높은 게임플레이 환경을 구축하는 데 집중했습니다.

---

## 📺 Project Showcase
- **Demonstration Video:** [영상링크]

---

## 🛠 Core Technical Implementations (C++)

### 🎯 Key Source Code: Grabber & TriggerComponent
단순한 이동을 넘어, 플레이어가 환경과 상호작용하고 퍼즐을 해결하는 메커니즘을 C++ 컴포넌트로 모듈화하여 구현했습니다.

#### **1. 물리 기반 상호작용 (Physics Handle & Raycasting)**
**SweepSingleByChannel**: GetWorld()->SweepSingleByChannel을 사용하여 플레이어 시선(Viewpoint)에서 물리적 충돌체를 감지합니다. 단순한 LineTrace 대신 구체(Sphere) 형태의 스윕을 사용하여 상호작용 판정을 관대하게 보정했습니다.

**Physics Handle**: 물체를 단순히 자식으로 부착(Attach)하는 것이 아니라, UPhysicsHandleComponent를 사용하여 물체의 질량과 관성을 유지한 채로 들어 올리고 이동시키는 사실적인 조작감을 구현했습니다.

#### **2. 모듈형 트리거 시스템 (Event Driven Architecture)**
다형성 및 재사용성: UTriggerComponent는 특정 액터에 종속되지 않고, Mover 인터페이스를 가진 어떤 액터(문, 비밀 벽, 함정 등)와도 연결될 수 있도록 설계되었습니다.

**Tag System**: 하드코딩된 참조 대신 ActorHasTag를 활용하여, 에디터 상에서 Tag 설정만으로 열쇠-자물쇠, 함정-발판 등의 짝을 유연하게 매칭했습니다.

#### **3. 동적 오브젝트 제어 (Mover)**
**상태 보간**: FMath::VInterpConstantTo를 사용하여 문이나 벽이 열리고 닫히는 동작을 프레임 레이트와 무관하게 부드럽게(Smooth) 처리했습니다.

**상대적 이동**: 월드 좌표가 아닌 GetOwner()->GetActorForwardVector() 등 로컬 벡터 연산을 통해, 레벨의 어느 방향에 배치해도 올바르게 작동하도록 구현했습니다.

---

## 📦 Assets & Resources
**Logic**: 캐릭터 이동, 물체 잡기, 문 개폐, 함정 로직 등 핵심 기능은 100% C++로 직접 구현되었습니다.

**Environment Assets**: 던전 분위기 조성을 위해 외부 에셋 팩을 활용하였습니다.

**Medieval Dungeon Asset Pack** (저장소 용량 최적화를 위해 .gitignore 처리됨)

---

## 💡 Problem Solving (Troubleshooting)
프로젝트 개발 과정에서 발생한 주요 이슈와 이를 해결하기 위한 기술적 접근 과정입니다.

### 1. 물리 충돌과 순간이동 문제 (The Tunneling Effect)
**Problem**: 

빠르게 움직이는 '압사 함정(Crushing Wall)'이 플레이어를 밀어내지 못하고 그대로 통과하거나, 플레이어가 벽 속에 갇히는 현상 발생. SetActorLocation으로 좌표를 강제 갱신하는 방식이 물리 엔진의 충돌 처리를 무시하는 것이 원인.

**Solution**: 

SetActorLocation 함수의 두 번째 인자인 bSweep을 true로 설정하여, 이동 경로상의 충돌을 감지하도록 수정.

고속 이동 물체에 대해 CCD (Continuous Collision Detection) 옵션을 활성화하여 프레임 사이의 충돌 누락 방지.

### 2. 트리거 로직의 한계와 확장 (Logic Reset)
**Problem**: 

함정 발판에서 플레이어가 벗어나는 순간 OnOverlapEnd가 호출되어, 닫히던 함정 벽이 다시 제자리로 돌아가 긴장감이 떨어지는 문제.

**Solution**:

bool IsOneShot 변수를 도입하여, 한 번 작동된 함정은 트리거 영역을 벗어나더라도 상태가 리셋되지 않도록 예외 처리 로직 추가 (if (IsOneShot) return;).

### 3. 하드코딩 제거와 유연성 확보 (Refactoring)
**Problem**: 

초기에는 Player, Unlock 등 태그 이름을 코드 내에 문자열로 고정(Hardcoding)했으나, "함정용 해골 벽"과 "탈출용 비밀 문"이 서로 다른 태그를 필요로 하면서 코드 수정이 불가피해짐.

**Solution**:

UPROPERTY(EditAnywhere) FName AcceptableActorTag;를 선언하여 태그 이름을 에디터에서 자유롭게 변경 가능하도록 수정.

생성자(Constructor)에서 기본값을 설정하여 기존에 배치된 액터들이 망가지지 않도록 하위 호환성 유지.

### 4. 조명에 따른 가시성 문제 (Visibility)
**Problem**: 

어두운 던전 환경과 동적 라이팅(Lumen)의 영향으로 엔딩 지점의 텍스트가 그림자에 가려 보이지 않음.

**Solution**:

Unlit 셰이딩 모델을 적용한 머티리얼을 제작하고, Emissive Color를 연결하여 주변 광원과 관계없이 자체 발광하도록 처리하여 시인성 확보.

---

## 🔧 Tech Stack
- **Engine**: Unreal Engine 5.6

- **Language**: C++ (Visual Studio 2022)

- **Version Control**: Git, GitHub
