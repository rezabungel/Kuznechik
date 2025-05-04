pipeline {
    agent { label "${params.jenkins_agent}" }

    parameters {
        string(name: "jenkins_agent", defaultValue: "ubuntu", trim: true, description: "Select the Jenkins agent")
        string(name: "branch", defaultValue: "main", trim: true, description: "Select the branch to build from")
        string(name: "container_tag", defaultValue: "0.0.1", trim: true, description: "Specify the tag for the container to be built")

        booleanParam(name: "test", defaultValue: false, description:"Enable or disable the Test stage")
        booleanParam(name: "secure_scanning", defaultValue: false, description: "Enable or disable the SecureScanning stage (SAST + SCA)")
        booleanParam(name: "build_docker", defaultValue: false, description: "Enable or disable the Build Docker stage")
        booleanParam(name: "docker_publish", defaultValue: false, description: "Enable or disable the Docker Publish stage (To enable, the Build Docker stage must be enabled)")
    }

    environment {
        DOCKER_REGISTRY = "ghcr.io"
        REPOSITORY = "rezabungel/kuznechik"
    }

    stages {
        stage("Checkout") {
            steps {
                echo "Start stage Checkout"
                git branch: "${params.branch}", url: "https://github.com/rezabungel/Kuznechik.git"
                echo "End stage Checkout"
            }
        }

        stage("Build") {
            steps {
                echo "Start stage Build"
                sh "g++ -DDEBUG -fPIC -shared -o lib/kuznechik.so src/encryption/kuznechik.cpp"
                echo "End stage Build"
            }
        }

        stage("Test") {
            when {
                expression { params.test }
            }
            steps {
                echo "Start stage Test"
                // TO DO: Tests
                echo "End stage Test"
            }
        }

        stage("SecureScanning") {
            when {
                expression { params.secure_scanning }
            }
            steps {
                echo "Start stage SecureScanning"
                sh "semgrep ci"
                echo "End stage SecureScanning"
            }
        }

        stage("Build Docker") {
            when {
                expression { params.build_docker }
            }
            steps {
                echo "Start stage Build Docker"
                sh "docker build -t ${env.DOCKER_REGISTRY}/${env.REPOSITORY}:${params.container_tag} ."
                echo "End stage Build Docker"
            }
        }

        stage("Docker Publish") {
            when {
                expression { params.build_docker && params.docker_publish }
            }
            steps {
                echo "Start stage Docker Publish"

                withCredentials([usernamePassword(credentialsId: "Token_for_packages", usernameVariable: "registry_username", passwordVariable: "registry_token")]) {
                    sh "docker login --username $registry_username --password $registry_token ${env.DOCKER_REGISTRY}"
                    sh "docker push ${env.DOCKER_REGISTRY}/${env.REPOSITORY}:${params.container_tag}"
                    sh "docker logout"
                }

                echo "End stage Docker Publish"
            }
        }
    }

    post {
        always {
            cleanWs()
        }
    }
}