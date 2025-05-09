pipeline {
    agent { label "${params.jenkins_agent}" }

    parameters {
        string(name: "jenkins_agent", defaultValue: "ubuntu", trim: true, description: "Select the Jenkins agent")
        string(name: "branch", defaultValue: "microservices", trim: true, description: "Select the branch to build from")
        string(name: "container_tag", defaultValue: "0.0.1", trim: true, description: "Specify the tag for the container to be built")

        booleanParam(name: "test", defaultValue: false, description:"Enable or disable the Test stage")
        booleanParam(name: "secure_scanning", defaultValue: false, description: "Enable or disable the SecureScanning stage (SAST + SCA)")
        booleanParam(name: "build_docker", defaultValue: false, description: "Enable or disable the Build Docker Images for Microservices stage")
        booleanParam(name: "docker_publish", defaultValue: false, description: "Enable or disable the Publish Docker Images for Microservices stage (To enable, the Build Docker Images for Microservices stage must be enabled)")
    }

    environment {
        DOCKER_REGISTRY = "ghcr.io"
        REPOSITORY = "rezabungel/kuznechik"
        SERVICES = "kuznechik_crypto,tools" // Microservices should be listed separated by ","
    }

    stages {
        stage("Checkout") {
            steps {
                echo "Start stage Checkout"
                git branch: "${params.branch}", url: "https://github.com/rezabungel/Kuznechik.git"
                echo "End stage Checkout"
            }
        }

        stage("Build kuznechik_crypto (C++)") {
            steps {
                echo "Start stage Build kuznechik_crypto (C++)"
                sh "g++ -DDEBUG -fPIC -shared -o lib/kuznechik.so src/kuznechik_crypto/encryption/kuznechik.cpp"
                echo "End stage Build kuznechik_crypto (C++)"
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

        stage("Build Docker Images for Microservices") {
            when {
                expression { params.build_docker }
            }
            steps {
                script {
                    echo "Start stage Build Docker Images for Microservices"

                    def services = env.SERVICES.split(',')
                    def parallel_stages = [:]

                    for (int i = 0; i < services.size(); i++) {
                        def service = services[i]
                        def dockerfile_path = "docker/${service}.Dockerfile"

                        parallel_stages["Build image for service: ${service}"] = {
                            stage("Build image for service: ${service}") {
                                echo "Start stage Build image for service: ${service}"
                                sh "docker build -t ${env.DOCKER_REGISTRY}/${env.REPOSITORY}/${service}:${params.container_tag} -f ${dockerfile_path} ."
                                echo "End stage Build image for service: ${service}"
                            }
                        }
                    }

                    parallel parallel_stages

                    echo "End stage Build Docker Images for Microservices"
                }
            }
        }

        stage("Publish Docker Images for Microservices") {
            when {
                expression { params.build_docker && params.docker_publish }
            }

            steps {
                script {
                    echo "Start stage Publish Docker Images for Microservices"

                    def services = env.SERVICES.split(',')
                    def parallel_stages = [:]

                    for (int i = 0; i < services.size(); i++) {
                        def service = services[i]

                        parallel_stages["Publish image for service: ${service}"] = {
                            stage("Publish image for service: ${service}") {
                                echo "Start stage Publish image for service: ${service}"
                                sh "docker push ${env.DOCKER_REGISTRY}/${env.REPOSITORY}/${service}:${params.container_tag}"
                                echo "End stage Publish image for service: ${service}"
                            }
                        }
                    }

                    withCredentials([usernamePassword(credentialsId: "Token_for_packages", usernameVariable: "registry_username", passwordVariable: "registry_token")]) {
                        sh "docker login --username $registry_username --password $registry_token ${env.DOCKER_REGISTRY}"
                        parallel parallel_stages
                        sh "docker logout"
                    }

                    echo "End stage Publish Docker Images for Microservices"
                }
            }
        }
    }

    post {
        always {
            cleanWs()
        }
    }
}