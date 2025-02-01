//--------------------
// kun 2025.01.31
//--------------------

#include "BaseWidgetComponent.h"
#include "Leeway/UMG/Widgets/BaseUserWidget.h"

void UBaseWidgetComponent::InitWidget()
{
    Super::InitWidget();
    if (auto* BaseUserWidget = Cast<UBaseUserWidget>(GetWidget()))
    {
        BaseUserWidget->SetOwningComponent(this);
    }
}
