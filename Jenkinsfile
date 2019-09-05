pipeline {
  agent any
  stages {
    stage('Message') {
      steps {
        echo 'test'
      }
    }
    stage('github check in') {
      parallel {
        stage('github check in') {
          steps {
            node(label: 'linux') {
              sleep 2
              sh 'date'
            }

          }
        }
        stage('error') {
          steps {
            node(label: 'linux') {
              sleep 5
              sh 'date'
            }

          }
        }
      }
    }
    stage('Finish Message') {
      steps {
        echo 'Finish'
      }
    }
    stage('mail') {
      steps {
        mail(subject: 'Test job finished', body: 'Check pipeline job', to: 'dariusz.schmidt@davita.com', from: 'no-reply@davita.com')
        withAnt(installation: 'test_inst', jdk: '8')
      }
    }
  }
  environment {
    test1 = '1'
    test2 = '2'
    test3 = '3'
  }
}