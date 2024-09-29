import uvicorn
from fastapi import FastAPI

from routes import get_apps_router
from config.project_config import settings


def get_application() -> FastAPI:
    application = FastAPI(
        title = settings.title,
        version = settings.version
    )

    application.include_router(get_apps_router())

    return application

app = get_application()


if __name__ == "__main__":
    uvicorn.run("main:app", host="0.0.0.0", reload=True)