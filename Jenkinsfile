pipeline {
  agent none
  stages {
    stage('Message') {
      steps {
        echo 'test'
      }
    }
    stage('error') {
      steps {
        node(label: 'linux') {
          sleep 2
        }

        sh 'date'
      }
    }
  }
  environment {
    test1 = '1'
    test2 = '2'
    test3 = '3'
  }
}