pipeline {
  agent none
  stages {
    stage('Message') {
      parallel {
        stage('Message') {
          steps {
            echo 'test'
          }
        }
        stage('git check in') {
          steps {
            timestamps()
            sh '''date
ls
pwd'''
          }
        }
      }
    }
  }
  environment {
    test1 = '1'
    test2 = '2'
    test3 = '3'
  }
}