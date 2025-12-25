// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"

#include "Engine/Engine.h"

#ifndef SCREENLOG
#define SCREENLOG(Color, Format, ...) \
    if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 20.0f, Color, FString::Printf(Format, ##__VA_ARGS__)); }
#endif

// Sets default values
AMyActor::AMyActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    SetActorLocation(StartLocation);

    if (GetWorldTimerManager().IsTimerActive(TimerHandle)) {
        GetWorldTimerManager().ClearTimer(TimerHandle);
    }
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyActor::RandomMoveAndTurn, 0.5f, true);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyActor::Move(const FVector& NewLocation) {
    TotalDistance += FVector::Distance(GetActorLocation(), NewLocation);
    SetActorLocation(NewLocation);
}

void AMyActor::Turn(const FRotator& NewRotation) {
    SetActorRotation(NewRotation);
}

void AMyActor::RandomMoveAndTurn() {
    if (MoveCount >= MaxMoveCount) {
        SCREENLOG(FColor::Yellow, TEXT("total distance: %.2f, event triggered count: %d"), TotalDistance, EventCount);
        GetWorldTimerManager().ClearTimer(TimerHandle);
        return;
    }

    MoveCount++;

    const FVector RandomLocation = FMath::RandPointInBox(FBox(MoveRangeMin, MoveRangeMax));
    const FRotator RandomRotation = FMath::VRand().Rotation();

    Move(RandomLocation);
    Turn(RandomRotation);

    SCREENLOG(FColor::Blue, TEXT("[%d/%d] Location: %s"), MoveCount, MaxMoveCount, *RandomLocation.ToCompactString());
    //SCREENLOG(FColor::Blue, TEXT("rotation: %s"), *NewRotation.ToString());

    if (EventTriggered()) {
        SCREENLOG(FColor::Green, TEXT("EVENT TRIGGERED"));
    }
}

bool AMyActor::EventTriggered() {
    if (FMath::FRand() >= EventProbability) {
        EventCount++;
        return true;
    }

    return false;
}
