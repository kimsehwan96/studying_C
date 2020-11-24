# 필요한 정보들

https://bodamnury.tistory.com/38



## 최종 텀프로젝트 구조

- 파일 리스트와 ip, port 번호를 리스트화 해서 갖고 있는 server가 존재
    - 각 유저는 server에 접속하여 자신의 디렉터리에 갖고있는 파일의 리스트를 업로드
        - 파일 양식은 1. test.c 192.168.0.120 5402 와 같이
            - 번호. {파일이름} {ip address} {port number} 형식으로 갖고있는다.
    - server concurrency 적용하여 여러 유저의 접속에 대해 대응 가능해야 한다.
        - 유저가 서버에 로그인 성공하였을때 유저들의 파일 목록(서버가 저장한)을 보고
            - 원하는 파일이 있다면 해당 유저와 P2P 연결을 하여 파일을 다운로드 받아야 함
        - 이 때 파일을 갖고있는 유저는 p2p server역할을 수행하면 될듯
        - client 프로그램은 p2p 요청을 하거나, 요청을 수락 할 때 fork 하여 통신을 하면 된다.
        - client의 p2p 요청 또한 server concurrency 구현 할 필요가 있다.
    
    