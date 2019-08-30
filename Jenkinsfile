pipeline {
  agent none
  stages {
    stage('Message') {
      steps {
        echo 'test'
      }
    }
    stage('') {
      steps {
        node(label: 'linux') {
          sleep 2
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