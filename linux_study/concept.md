# 리눅스 프로그래밍의 개념

## 파일과 파일 시스템
    파일은 리눅스에서 가장 기본이고 핵심이 되는 추상화 개념이다.
    리눅스의 모든 것은 파일이라는 철학을 따른다. 모든 인터렉션은 실제로 파일이 아닌 것 처럼 보이더라도
    파일을 읽고 파일을 쓰는 것으로 이루어진다. 파일에 접근하려면 먼저 파일을 열어야 한다.
    파일은 읽기, 쓰기, 읽기/쓰기 모드로 열 수 있다. 이렇게 열린 파일은 그 파일에 대한 메타데이터와 연결된 고유한 기술자를 통해 참조 할 수 있다. (descriptor)
    이 디스크립터는 정수로 표현되며 파일 디스크립터라고 표현. fd라고 보통 사용한다.
    리눅스 시스템 프로그래밍은 이 fd를 열고 조작하고 닫는 작업이다.

## 일반 파일

    우리가 흔히 파일이라고 부르는 것은 일반 파일을 의미한다. 일반 파일은 바이트 스트림이라고 부르는 연속적으로
    나열된 바이트 배열에 저장된 데이터를 의미한다. 리눅스에는 파일을 위한 특별한 자료구조가 없다,
    이 데이터에는 어떠한 값이라도 들어 갈 수 있으며 어떤 구조로 저장해도 상관 없다.
    
    파일은 바이트를 읽고 쓰는 것이 가능하다. 이런 작업은 파일 내부의 위치를 지정해서 수행 할 수 있는데, 이 위치는 파일 오프셋 혹은 파일 위치라고 한다. 파일 오프셋은 커널이 열린 파일마다 유지하는 메타데이터의 핵심이다. 파일이 처음 열리면 파일 오프셋은 0이다. 보통 파일은 바이트 단위로 읽고 쓰기 때문에 파일 오프셋 역시 바이트 단위로 증가하거나 감소한다. 파일의 시작위치보다 앞선 위치에 데이터를 기록하는 것은 불가능하다. 파일 중간에 데이터를 기록하면 전에 있던 데이ㅓ를 덮어쓴다. 파일을 쓰는 작업의 대부분은 파일 끝에서 일어난다.

    하나의 파일은 다른 프로세서나 심지어 동일한 프로세스에서 한 번 이상 열 수 있다.
    파일은 열릴 때마다 고유한 파일 디스크립터를 반환한다. 반대로 프로세스에서는 파일 디스크립터를 공유 할 수 있다.
    하나의 파일 디스크립터는 하나 이상의 프로세스에서 사용 될 수 있다. 

    파일 이름을 통해 파일에 접근하지만 실제로는 파일은 파일 이름과 직접적으로 연관 되어있지는 않고
    inode 라고 하는 파일 시스템 내에서만 고유한 정수값으로 참조된다.
    inode는 변경된 날짜, 소유자, 타입, 길이, 데이터 저장위치 같은 메타데이터를 저장하고 있지만 파일 이름은 저장하지 않는다 !!

## 디렉터리와 링크

    inode 번호로 파일에 접근하면 귀찮다. 그래서 파일 이름으로 접근을 한다. 디렉터리는 파일에 접근하기 위한 이름을 제공하는데 디렉터리는 inode 대신 사람이 읽을 수 있는 이름으로 나타낸다. 이 이름과 inode 쌍을 링크라고 한다.

    사용자 영역 애플리케이션에서 어떤 파일을 열ㄹ겠다고 요청하면 커널은 파일 이름이 포함된 디렉터리를 열고 파일을 찾는다. 커널은 파일 이름으로 inode 번호를 얻고, 이렇게 얻은 inode번호로 inode를 찾는다.

    수 많은 디렉터리에서 특정한 디렉터리를 어떻게 찾을까? 디렉터리도 inode가 있다. 디렉터리 내부의 링크 역시 다른 디렉터리의 inode를 가르킬수있다. 

## 상대경로와 절대경로
    루트 디렉터리에서 시작하는 경로 이름은 언제나 완전하게 명시 되어있기 때문에 절대경로라고 한다.
    ex :) /home/pi/test/test.py
    상대 경로 : 완전히 명시되어있지 않고 다른 디렉터리의 상대적인 위치로 표현한다 (ex: todo/plan)
    
    예를 들어 todo/plan 을 찾는다고 하면 현재 작업 디렉터리에서 todo 디렉터리를 탐색한다. 여기서 커널은 Plan을 가르키는 inode를 찾는 것.

` 리눅스 환경 터미널에서 ls -i를 하면 inode 값 확인 가능 `

## hardlink