# studying_C

# 환경 : VScode

# VScode에서 C/C++을 컴파일 하기 위해서는 extensions를 설치해야 한다.

# 설치 이후 tasks.json 파일을 작성해 빌드시 필요한 명령어들을 자동 실행되게 한다.

"command": "gcc",
            "args": [
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}"
            ],
            "group": "build",


` command (명령어) : gcc `

` gcc ${file} foo bar ....` 