from fastapi import APIRouter


health_router = APIRouter(prefix="/health", tags=["health"])

@health_router.get("/liveness", status_code=200)
async def liveness_probe() -> dict[str, str]:
    """
    Liveness probe endpoint to indicate if the application is running.
    """

    return {"status": "alive"}