// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#define SCREENLOG(Color, Format, ...) \
    if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 20.0f, Color, FString::Printf(Format, ##__VA_ARGS__)); }

#include "MyActor.generated.h"

UCLASS()
class NBCASSIGNMENT5_API AMyActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void Move(const FVector& NewLocation);
    void Turn(const FRotator& NewRotation);
    void RandomMoveAndTurn();

    UPROPERTY(EditAnywhere, Category = "Settings")
    FVector StartLocation;

    UPROPERTY(EditAnywhere, Category = "Settings")
    int32 TotalMoveCount;

private:
    int32 MoveCount;
    FTimerHandle TimerHandle;
    int32 EventCount;
    double TotalDistance;

    bool EventTriggered();
};
