//--------------------
// kun 2025.02.03
//--------------------

#include "Leeway/PreEngine/Runtime/Core/Public/DebugUtils/LWDebugUtils.h"

namespace NSLeeway
{
    int DrawDebugLevel_All = 0;
    static FAutoConsoleVariableRef CVar_LW_DrawDebug_All(
        TEXT("lw.debug.draw.all"), DrawDebugLevel_All,
        TEXT("dong de dou dong!"),
        ECVF_Default);
}

namespace NSLeeway
{
    void DrawDebugLine(int DebugLevel, const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugLine(InWorld, LineStart, LineEnd, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugPoint(int DebugLevel, const UWorld* InWorld, FVector const& Position, float Size, FColor const& PointColor, bool bPersistentLines, float LifeTime, uint8 DepthPriority)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugPoint(InWorld, Position, Size, PointColor, bPersistentLines, LifeTime, DepthPriority);
    }
    void DrawDebugDirectionalArrow(int DebugLevel, const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, float ArrowSize, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugDirectionalArrow(InWorld, LineStart, LineEnd, ArrowSize, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugBox(int DebugLevel, const UWorld* InWorld, FVector const& Center, FVector const& Extent, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugBox(InWorld, Center, Extent, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugBox(int DebugLevel, const UWorld* InWorld, FVector const& Center, FVector const& Extent, const FQuat& Rotation, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugBox(InWorld, Center, Extent, Rotation, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugCoordinateSystem(int DebugLevel, const UWorld* InWorld, FVector const& AxisLoc, FRotator const& AxisRot, float Scale, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCoordinateSystem(InWorld, AxisLoc, AxisRot, Scale, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugCrosshairs(int DebugLevel, const UWorld* InWorld, FVector const& AxisLoc, FRotator const& AxisRot, float Scale, const FColor& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCrosshairs(InWorld, AxisLoc, AxisRot, Scale, Color, bPersistentLines, LifeTime, DepthPriority);
    }
    void DrawDebugCircle(int DebugLevel, const UWorld* InWorld, const FMatrix& TransformMatrix, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness, bool bDrawAxis)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCircle(InWorld, TransformMatrix, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness, bDrawAxis);
    }
    void DrawDebugCircle(int DebugLevel, const UWorld* InWorld, FVector Center, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness, FVector YAxis, FVector ZAxis, bool bDrawAxis)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCircle(InWorld, Center, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness, YAxis, ZAxis, bDrawAxis);
    }
    void DrawDebugCircleArc(int DebugLevel, const UWorld* InWorld, FVector const& Center, float Radius, FVector const& Direction, float AngleWidth, int32 Segments, const FColor& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCircleArc(InWorld, Center, Radius, Direction, AngleWidth, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebug2DDonut(int DebugLevel, const UWorld* InWorld, const FMatrix& TransformMatrix, float InnerRadius, float OuterRadius, int32 Segments, const FColor& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebug2DDonut(InWorld, TransformMatrix, InnerRadius, OuterRadius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugSphere(int DebugLevel, const UWorld* InWorld, FVector const& Center, float Radius, int32 Segments, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugSphere(InWorld, Center, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugCylinder(int DebugLevel, const UWorld* InWorld, FVector const& Start, FVector const& End, float Radius, int32 Segments, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCylinder(InWorld, Start, End, Radius, Segments, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugCone(int DebugLevel, const UWorld* InWorld, FVector const& Origin, FVector const& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCone(InWorld, Origin, Direction, Length, AngleWidth, AngleHeight, NumSides, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugAltCone(int DebugLevel, const UWorld* InWorld, FVector const& Origin, FRotator const& Rotation, float Length, float AngleWidth, float AngleHeight, FColor const& DrawColor, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugAltCone(InWorld, Origin, Rotation, Length, AngleWidth, AngleHeight, DrawColor, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugString(int DebugLevel, const UWorld* InWorld, FVector const& TextLocation, const FString& Text, AActor* TestBaseActor, FColor const& TextColor, float Duration, bool bDrawShadow, float FontScale)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugString(InWorld, TextLocation, Text, TestBaseActor, TextColor, Duration, bDrawShadow, FontScale);
    }
    void DrawDebugFrustum(int DebugLevel, const UWorld* InWorld, const FMatrix& FrustumToWorld, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugFrustum(InWorld, FrustumToWorld, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawCircle(int DebugLevel, const UWorld* InWorld, const FVector& Base, const FVector& X, const FVector& Y, const FColor& Color, float Radius, int32 NumSides, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawCircle(InWorld, Base, X, Y, Color, Radius, NumSides, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugCapsule(int DebugLevel, const UWorld* InWorld, FVector const& Center, float HalfHeight, float Radius, const FQuat& Rotation, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCapsule(InWorld, Center, HalfHeight, Radius, Rotation, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawDebugCamera(int DebugLevel, const UWorld* InWorld, FVector const& Location, FRotator const& Rotation, float FOVDeg, float Scale, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCamera(InWorld, Location, Rotation, FOVDeg, Scale, Color, bPersistentLines, LifeTime, DepthPriority);
    }
    void DrawCentripetalCatmullRomSpline(int DebugLevel, const UWorld* InWorld, TConstArrayView<FVector> Points, FColor const& Color, float Alpha, int32 NumSamplesPerSegment, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawCentripetalCatmullRomSpline(InWorld, Points, Color, Alpha, NumSamplesPerSegment, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void DrawCentripetalCatmullRomSpline(int DebugLevel, const UWorld* InWorld, TConstArrayView<FVector> Points, TConstArrayView<FColor> Colors, float Alpha, int32 NumSamplesPerSegment, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawCentripetalCatmullRomSpline(InWorld, Points, Colors, Alpha, NumSamplesPerSegment, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }
    void FlushDebugStrings(int DebugLevel, const UWorld* InWorld)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            FlushDebugStrings(InWorld);
    }
    void DrawDebugSolidBox(int DebugLevel, const UWorld* InWorld, FBox const& Box, FColor const& Color, const FTransform& Transform, bool bPersistent, float LifeTime, uint8 DepthPriority)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugSolidBox(InWorld, Box, Color, Transform, bPersistent, LifeTime, DepthPriority);
    }
    void DrawDebugSolidBox(int DebugLevel, const UWorld* InWorld, FVector const& Center, FVector const& Extent, FColor const& Color, bool bPersistent, float LifeTime, uint8 DepthPriority)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugSolidBox(InWorld, Center, Extent, Color, bPersistent, LifeTime, DepthPriority);
    }
    void DrawDebugSolidBox(int DebugLevel, const UWorld* InWorld, FVector const& Center, FVector const& Extent, FQuat const& Rotation, FColor const& Color, bool bPersistent, float LifeTime, uint8 DepthPriority)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugSolidBox(InWorld, Center, Extent, Rotation, Color, bPersistent, LifeTime, DepthPriority);
    }
    void DrawDebugMesh(int DebugLevel, const UWorld* InWorld, TArray<FVector> const& Verts, TArray<int32> const& Indices, FColor const& Color, bool bPersistent, float LifeTime, uint8 DepthPriority)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugMesh(InWorld, Verts, Indices, Color, bPersistent, LifeTime, DepthPriority);
    }
    void DrawDebugSolidPlane(int DebugLevel, const UWorld* InWorld, FPlane const& P, FVector const& Loc, float Size, FColor const& Color, bool bPersistent, float LifeTime, uint8 DepthPriority)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugSolidPlane(InWorld, P, Loc, Size, Color, bPersistent, LifeTime, DepthPriority);
    }
    void DrawDebugSolidPlane(int DebugLevel, const UWorld* InWorld, FPlane const& P, FVector const& Loc, FVector2D const& Extents, FColor const& Color, bool bPersistent, float LifeTime, uint8 DepthPriority)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugSolidPlane(InWorld, P, Loc, Extents, Color, bPersistent, LifeTime, DepthPriority);
    }
    void DrawDebugFloatHistory(int DebugLevel, UWorld const& WorldRef, FDebugFloatHistory const& FloatHistory, FTransform const& DrawTransform, FVector2D const& DrawSize, FColor const& DrawColor, bool const& bPersistent, float const& LifeTime, uint8 const& DepthPriority)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugFloatHistory(WorldRef, FloatHistory, DrawTransform, DrawSize, DrawColor, bPersistent, LifeTime, DepthPriority);
    }
    void DrawDebugFloatHistory(int DebugLevel, UWorld const& WorldRef, FDebugFloatHistory const& FloatHistory, FVector const& DrawLocation, FVector2D const& DrawSize, FColor const& DrawColor, bool const& bPersistent, float const& LifeTime, uint8 const& DepthPriority)
    {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugFloatHistory(WorldRef, FloatHistory, DrawLocation, DrawSize, DrawColor, bPersistent, LifeTime, DepthPriority);
    }
    void DrawDebugCanvas2DLine(int DebugLevel, UCanvas* Canvas, const FVector& Start, const FVector& End, const FLinearColor& LineColor) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCanvas2DLine(Canvas, Start, End, LineColor);
    }
    void DrawDebugCanvas2DLine2(int DebugLevel, UCanvas* Canvas, const FVector2D& StartPosition, const FVector2D& EndPosition, const FLinearColor& LineColor, const float& LineThickness) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCanvas2DLine(Canvas, StartPosition, EndPosition, LineColor, LineThickness);
    }
    void DrawDebugCanvas2DCircle(int DebugLevel, UCanvas* Canvas, const FVector2D& Center, float Radius, int32 NumSides, const FLinearColor& LineColor, const float& LineThickness) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCanvas2DCircle(Canvas, Center, Radius, NumSides, LineColor, LineThickness);
    }
    void DrawDebugCanvas2DBox(int DebugLevel, UCanvas* Canvas, const FBox2D& Box, const FLinearColor& LineColor, const float& LineThickness) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCanvas2DBox(Canvas, Box, LineColor, LineThickness);
    }
    void DrawDebugCanvasLine(int DebugLevel, UCanvas* Canvas, const FVector& Start, const FVector& End, const FLinearColor& LineColor) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCanvasLine(Canvas, Start, End, LineColor);
    }
    void DrawDebugCanvasHalfCircle(int DebugLevel, UCanvas* Canvas, const FVector& Base, const FVector& X, const FVector& Y, FColor Color, float Radius, int32 NumSides) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCanvasHalfCircle(Canvas, Base, X, Y, Color, Radius, NumSides);
    }
    void DrawDebugCanvasWireCone(int DebugLevel, UCanvas* Canvas, const FTransform& Transform, float ConeRadius, float ConeAngle, int32 ConeSides, FColor Color) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCanvasWireCone(Canvas, Transform, ConeRadius, ConeAngle, ConeSides, Color);
    }
    void DrawDebugCanvasCircle(int DebugLevel, UCanvas* Canvas, const FVector& Base, const FVector& X, const FVector& Y, FColor Color, float Radius, int32 NumSides) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCanvasCircle(Canvas, Base, X, Y, Color, Radius, NumSides);
    }
    void DrawDebugCanvasWireSphere(int DebugLevel, UCanvas* Canvas, const FVector& Base, FColor Color, float Radius, int32 NumSides) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCanvasWireSphere(Canvas, Base, Color, Radius, NumSides);
    }
    void DrawDebugCanvasWireBox(int DebugLevel, UCanvas* Canvas, const FMatrix& Transform, const FBox& Box, FColor Color) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCanvasWireBox(Canvas, Transform, Box, Color);
    }
    void DrawDebugCanvasCapsule(int DebugLevel, UCanvas* Canvas, const FMatrix& Transform, float HalfLength, float Radius, const FColor& LineColor) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCanvasCapsule(Canvas, Transform, HalfLength, Radius, LineColor);
    }
}

namespace NSLeeway
{
    void DrawDebugCharacter(ACharacter* Character, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (Character)
        {
            DrawDebugCapsuleComponent(Character->GetCapsuleComponent(), Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
        }
    }

    void DrawDebugCapsuleComponent(UCapsuleComponent* CapsuleComp, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
    {
        if (CapsuleComp)
        {
            DrawDebugCapsule(CapsuleComp->GetWorld(), CapsuleComp->GetComponentLocation(), CapsuleComp->GetScaledCapsuleHalfHeight(), CapsuleComp->GetScaledCapsuleRadius(), CapsuleComp->GetComponentQuat(), Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
        }
    }

    void DrawDebugSection(UWorld* World, FVector const& Center, float Radius, float DegreeThreshold, FQuat Rotation, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness, int Segments)
    {
        if (!World)
        {
            return; // 确保 World 有效
        }

        // 计算扇形区域的左右边界角度
        float HalfAngle = DegreeThreshold * 0.5f;
        float StartAngle = -HalfAngle;
        float EndAngle = HalfAngle;

        // 计算每个分段的角度增量
        float AngleIncrement = DegreeThreshold / Segments;

        // 获取旋转后的前向和上方向量
        FVector Forward = Rotation.GetForwardVector();
        FVector Up = Rotation.GetUpVector();

        // 绘制扇形区域的边界线
        FVector StartDir = Forward.RotateAngleAxis(StartAngle, Up);
        FVector EndDir = Forward.RotateAngleAxis(EndAngle, Up);

        FVector StartPoint = Center + StartDir * Radius;
        FVector EndPoint = Center + EndDir * Radius;

        DrawDebugLine(World, Center, StartPoint, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
        DrawDebugLine(World, Center, EndPoint, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);

        // 绘制扇形区域的圆弧
        FVector PreviousPoint = StartPoint;
        for (int i = 1; i <= Segments; i++)
        {
            float Angle = StartAngle + i * AngleIncrement;
            FVector CurrentDir = Forward.RotateAngleAxis(Angle, Up);
            FVector CurrentPoint = Center + CurrentDir * Radius;

            DrawDebugLine(World, PreviousPoint, CurrentPoint, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
            PreviousPoint = CurrentPoint;
        }
    }

    void DrawDebugCharacter(int DebugLevel, ACharacter* Character, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCharacter(Character, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }

    void DrawDebugCapsuleComponent(int DebugLevel, UCapsuleComponent* CapsuleComp, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugCapsuleComponent(CapsuleComp, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
    }

    void DrawDebugSection(int DebugLevel, UWorld* World, FVector const& Center, float Radius, float DegreeThreshold, FQuat Rotation, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness, int Segments) {
        if (DrawDebugLevel_All >= DebugLevel)
            DrawDebugSection(World, Center, Radius, DegreeThreshold, Rotation, Color, bPersistentLines, LifeTime, DepthPriority, Thickness, Segments);
    }
}