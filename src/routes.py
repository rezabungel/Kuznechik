from fastapi import APIRouter

from health.router import health_router
from tools.router import tools_router
from encryption.router import router as router_kuznechik


def get_apps_router() -> APIRouter:
    router = APIRouter()

    router.include_router(health_router)
    router.include_router(tools_router)
    router.include_router(router_kuznechik)

    return router